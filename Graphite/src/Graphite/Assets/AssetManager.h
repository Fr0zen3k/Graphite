//
// Created by Mauricio Smit
//
#pragma once

#include "Graphite/Core/grpch.h"

namespace Graphite
{
	class Asset;

	class Texture;
	class Animation2D;
	class Scene;

	class AssetManager
	{
	public:
		static AssetManager& instance();

		Texture* GetTexture(const std::string& filename);
		Animation2D* GetAnimation(const std::string& filename);
		Scene* GetScene(const std::string& filename);

		void FreeAsset(const std::string& filename);

	private:
		std::map<std::string, std::unique_ptr<Asset>> mAssetsPerFilename;
	};

}