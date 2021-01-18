//
// Created by Mauricio Smit
//
#pragma once

#include "Graphite/Core/grpch.h"

#include "Asset.h"

#include "glm/glm.hpp"

namespace Graphite
{
	class Texture;// Internal texture

	class GRAPHITE_API TextureAsset : public Asset
	{
	public:
		TextureAsset();
		~TextureAsset();

		void Load(std::istream& source);
		void Unload();

		inline size_t GetOriginalWidth() const { return mWidth; }
		inline size_t GetOriginalHeight() const { return mHeight; }

	protected:
		Texture *mInternalTexture;
		size_t mWidth, mHeight;
	};

}