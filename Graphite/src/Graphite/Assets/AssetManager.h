//
// Created by Mauricio Smit
//
#pragma once

#include "Graphite/Core/grpch.h"

namespace Graphite
{
	class Asset;

	class TextureAsset;
	class Animation2DAsset;
	class Scene2D;

	struct AssetManagementData
	{
		std::unique_ptr<Asset> asset = nullptr;
		size_t counter = 0;
	};
	using AssetMap = std::map<std::string, AssetManagementData>;
	using AssetMapIterator = AssetMap::iterator;

	class AssetManager
	{
	public:
		static AssetManager& instance();

		// Returns the asset corresponding to the given filename. The asset isn't necessarily loaded.
		// If it doesn't exist returns nullptr
		AssetPtr<Asset> GetAsset(const std::string& filename);

		AssetPtr<TextureAsset> GetTexture(const std::string& filename);
		AssetPtr<Animation2DAsset> GetAnimation(const std::string& filename);
		AssetPtr<Scene2D> GetScene2D(const std::string& filename);

		void LoadAsset(const std::string& filename);
		void FreeAsset(const std::string& filename);

	private:
		AssetMap mAssetsPerFilename;
		std::map<std::string, AssetPtr<Asset>> mLoadedAssetsPerFilename;

		AssetManager();
	};

	template<class _AssT>
	class AssetPtr
	{
	public:
		AssetPtr() :
			mAssetMapPtr(nullptr),
			mAssetIterator()
		{
		}

		AssetPtr(AssetMap* mapPtr, AssetMapIterator it) :
			mAssetMapPtr(mapPtr),
			mAssetIterator(it)
		{
			if (mAssetMapPtr)
				mAssetIterator->second.counter++;
		}

		AssetPtr(const AssetPtr<_AssT>& other) :
			mAssetMapPtr(other.mAssetMapPtr),
			mAssetIterator(other.mAssetIterator)
		{
			if (mAssetMapPtr)
				mAssetIterator->second.counter++;
		}

		~AssetPtr()
		{
			if (mAssetMapPtr)
			{
				mAssetIterator->second.counter--;
				if (mAssetIterator->second.counter == 0)
				{
					mAssetMapPtr->erase(mAssetIterator);
					mAssetMapPtr = nullptr;
				}
			}
		}

		AssetPtr<_AssT>& operator=(const AssetPtr<_AssT>& other)
		{
			if (mAssetMapPtr)
			{
				mAssetIterator->second.counter--;
				if (mAssetIterator->second.counter == 0)
				{
					mAssetMapPtr->erase(mAssetIterator);
					mAssetMapPtr = nullptr;
				}
			}

			mAssetMapPtr = other.mAssetMapPtr;
			mAssetIterator = other.mAssetIterator;

			if (mAssetMapPtr)
				mAssetIterator->second.counter++;
			return *this;
		}

		bool operator==(const AssetPtr<_AssT>& other) const
		{
			return mAssetIterator->second.asset == other.mAssetIterator->second.asset;
		}

		bool operator!=(const AssetPtr<_AssT>& other) const
		{
			return mAssetIterator->second.asset != other.mAssetIterator->second.asset;
		}

		bool operator>(const AssetPtr<_AssT>& other) const
		{
			return mAssetIterator->second.asset > other.mAssetIterator->second.asset;
		}

		bool operator<(const AssetPtr<_AssT>& other) const
		{
			return mAssetIterator->second.asset < other.mAssetIterator->second.asset;
		}

		bool operator>=(const AssetPtr<_AssT>& other) const
		{
			return mAssetIterator->second.asset >= other.mAssetIterator->second.asset;
		}

		bool operator<=(const AssetPtr<_AssT>& other) const
		{
			return mAssetIterator->second.asset <= other.mAssetIterator->second.asset;
		}

		bool isValid() const
		{
			return mAssetMapPtr != nullptr;
		}

		_AssT& operator*()
		{
			return *dynamic_cast<_AssT*>(mAssetIterator->second.asset);
		}

		_AssT* operator->()
		{
			return dynamic_cast<_AssT*>(mAssetIterator->second.asset);
		}

		template<class _OtherT>
		operator AssetPtr<_OtherT>()
		{
			_OtherT* other = dynamic_cast<_OtherT*>(mAssetIterator->second.asset);
			if (other == nullptr)
			{
				throw std::bad_cast("Cannot cast!");
			}

			return AssetPtr<_OtherT>(mAssetMapPtr, mAssetIterator);
		}

	protected:
		AssetMap* mAssetMapPtr;
		AssetMapIterator mAssetIterator;
	};

}