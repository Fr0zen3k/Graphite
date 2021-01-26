//
// Created by Mauricio Smit
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_ASSETMANAGER_H
#define GRAPHITE_ASSETMANAGER_H

#include "Graphite/Core/grpch.h"

#include "Graphite/Core/Core.h"

#include "Asset.h"

namespace Graphite
{
	class TextureAsset;
	class Animation2DAsset;
	class Scene2D;

	struct GRAPHITE_API AssetManagementData
	{
		std::shared_ptr<Asset> asset;
		size_t counter = 0;
	};
	using AssetMap = std::map<std::string, AssetManagementData>;
	using AssetMapIterator = AssetMap::iterator;

	template<class _AssT>
	class GRAPHITE_API AssetPtr
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
			return *dynamic_cast<_AssT*>(mAssetIterator->second.asset.get());
		}

		_AssT* operator->()
		{
			return dynamic_cast<_AssT*>(mAssetIterator->second.asset.get());
		}

		template<class _OtherT>
		operator AssetPtr<_OtherT>()
		{
			_OtherT* other = dynamic_cast<_OtherT*>(mAssetIterator->second.asset.get());
			if (other == nullptr)
			{
				throw std::bad_cast();
			}

			return AssetPtr<_OtherT>(mAssetMapPtr, mAssetIterator);
		}

	protected:
		AssetMap* mAssetMapPtr;
		AssetMapIterator mAssetIterator;
	};

	class GRAPHITE_API AssetManager
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

}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif