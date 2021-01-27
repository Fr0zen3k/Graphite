#include "Graphite/Core/grpch.h"
#include "AssetManager.h"
#include "TextureAsset.h"
#include "Animation2DAsset.h"
#include "Graphite/Scene/Scene2D/Scene2D.h"

#include <fstream>

namespace Graphite
{
	AssetManager& AssetManager::instance()
	{
		static AssetManager in;
		return in;
	}

	AssetManager::AssetManager()
	{
	}

	AssetPtr<Asset> AssetManager::GetAsset(const std::string& filename)
	{
		auto it = mAssetsPerFilename.find(filename);
		if (it == mAssetsPerFilename.end())
		{
			std::shared_ptr<Asset> newAssetPtr = nullptr;

			std::string ext = filename.substr(filename.find_last_of('.') + 1);
			if (ext == "scene")
			{
				newAssetPtr = std::make_shared<Scene2D>();
			}
			else if (ext == "anim2d")
			{
				newAssetPtr = std::make_shared<Animation2DAsset>();
			}
			else if (ext == "png" || ext == "jpg" || ext == "bmp")
			{
				newAssetPtr = std::make_shared<TextureAsset>();
			}

			it = mAssetsPerFilename.insert({
				filename,
				AssetManagementData{newAssetPtr, 0}
				}).first;
		}

		return AssetPtr<Asset>(&mAssetsPerFilename, it);
	}

	AssetPtr<TextureAsset> AssetManager::GetTexture(const std::string& filename)
	{
		return GetAsset(filename);
	}

	AssetPtr<Animation2DAsset> AssetManager::GetAnimation(const std::string& filename)
	{
		return GetAsset(filename);
	}

	AssetPtr<Scene2D> AssetManager::GetScene2D(const std::string& filename)
	{
		return GetAsset(filename);
	}

	void AssetManager::LoadAsset(const std::string& filename)
	{
		auto assetPtr = GetAsset(filename);
		if (!assetPtr->IsLoaded())
		{
			std::ifstream file;

			if (assetPtr->NeedsBinary())
				file.open(filename, std::ios::binary);
			else
				file.open(filename);

			assetPtr->Load(file);
			mLoadedAssetsPerFilename[filename] = assetPtr;
		}
	}

	void AssetManager::FreeAsset(const std::string& filename)
	{
		auto assetPtr = GetAsset(filename);
		if (assetPtr->IsLoaded())
		{
			assetPtr->Unload();
			mLoadedAssetsPerFilename.erase(filename);
		}
	}
}