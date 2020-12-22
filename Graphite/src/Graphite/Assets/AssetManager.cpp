#include "AssetManager.h"

namespace Graphite
{
	AssetManager& AssetManager::instance()
	{
		static AssetManager in;
		return in;
	}
	Asset* AssetManager::GetAsset(const std::string& filename)
	{
		return nullptr;
	}
	Texture* AssetManager::GetTexture(const std::string& filename)
	{
		return nullptr;
	}
	Animation2D* AssetManager::GetAnimation(const std::string& filename)
	{
		return nullptr;
	}
	Scene* AssetManager::GetScene(const std::string& filename)
	{
		return nullptr;
	}
	void AssetManager::LoadAsset(const std::string& filename)
	{
	}
	void AssetManager::FreeAsset(const std::string& filename)
	{
		mAssetsPerFilename.erase(filename);
	}
}