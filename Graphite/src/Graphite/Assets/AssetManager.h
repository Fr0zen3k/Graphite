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
	class Scene;

	class AssetManager
	{
	public:
		static AssetManager& instance();

		// Returns the asset corresponding to the given filename. The asset isn't necessarily loaded.
		// If it doesn't exist returns nullptr
		Asset* GetAsset(const std::string& filename);

		TextureAsset* GetTexture(const std::string& filename);
		Animation2DAsset* GetAnimation(const std::string& filename);
		Scene* GetScene(const std::string& filename);

		void LoadAsset(const std::string& filename);
		void FreeAsset(const std::string& filename);

	private:
		std::map<std::string, std::unique_ptr<Asset>> mAssetsPerFilename;
	};

	template<class _AssT>
	class AssetReference
	{
	public:

	};

}