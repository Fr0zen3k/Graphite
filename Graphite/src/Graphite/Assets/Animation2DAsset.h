//
// Created by Mauricio Smit
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_ANIMATION2DASSET_H
#define GRAPHITE_ANIMATION2DASSET_H

#include "Graphite/Core/grpch.h"

#include "Graphite/Core/Core.h"

#include "Asset.h"

#include "glm/glm.hpp"

#include "TextureAsset.h"

#include "AssetManager.h"

template<class _AssT>
class AssetPtr;

namespace Graphite
{
	class TextureAsset;

	class GRAPHITE_API Frame2D
	{
	public:
		Frame2D(AssetPtr<const TextureAsset> tex, glm::vec2 topLeft, glm::vec2 bottomRight, float w, float h);
		~Frame2D();

		AssetPtr<const TextureAsset> GetTexture() const { return mTexturePtr; }
		glm::vec2 GetTopLeft() const { return mTopLeft; }
		glm::vec2 GetBottomRight() const { return mBottomRight; }
		float GetWidth() const { return mWidth; }
		float GetHeight() const { return mHeight; }

	protected:
		AssetPtr<const TextureAsset> mTexturePtr;
		glm::vec2 mTopLeft, mBottomRight;
		float mWidth, mHeight;
	};


	// A sprite animation
	class GRAPHITE_API Animation2DAsset : public Asset
	{
	public:
		Animation2DAsset();
		~Animation2DAsset();

		void Load(std::istream& source);
		void Load(const rapidjson::Value& params);
		void Unload();

		inline Frame2D& GetFrame(size_t index) const { return mFrames[index]; }

	protected:
		std::vector<Frame2D> mFrames;
	};

}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif