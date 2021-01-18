#include "AssetManager.h"
#include "TextureAsset.h"
#include "Animation2DAsset.h"
#include "Graphite/Scene/Scene2D/Scene2D.h"

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
			Asset* newAsset = nullptr;

			std::string ext = filename.substr(filename.find_last_of('.') + 1);
			if (ext == "scene")
			{
				Asset* newAsset = new Scene2D();
			}
			else if (ext == "anim2d")
			{
				Asset* newAsset = new Animation2DAsset();
			}
			else if (ext == "png" || ext == "jpg" || ext == "bmp")
			{
				Asset* newAsset = new TextureAsset();
			}

			it = mAssetsPerFilename.insert({
				filename,
				AssetManagementData{
					std::make_unique<Asset>(newAsset),
					0
				}
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
		mLoadedAssetsPerFilename[filename] = GetAsset(filename);
	}

	void AssetManager::FreeAsset(const std::string& filename)
	{
		mLoadedAssetsPerFilename.erase(filename);
	}
}