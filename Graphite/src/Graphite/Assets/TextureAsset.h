//
// Created by Mauricio Smit
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_TEXTUREASSET_H
#define GRAPHITE_TEXTUREASSET_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "Asset.h"

#include "Graphite/Renderer/RendererCore/Texture.h"

namespace Graphite
{

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

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif