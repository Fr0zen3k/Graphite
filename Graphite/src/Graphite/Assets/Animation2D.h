//
// Created by Mauricio Smit
//
#pragma once

#include "Graphite/Core/grpch.h"

#include "Asset.h"

#include "glm/glm.hpp"

namespace Graphite
{
	class Texture;

	class GRAPHITE_API Frame2D
	{
	public:
		Frame2D(const Texture* tex, glm::vec2 topLeft, glm::vec2 bottomRight, float w, float h);
		~Frame2D();

		const Texture* GetTexture() const { return mTexturePtr; }
		glm::vec2 GetTopLeft() const { return mTopLeft; }
		glm::vec2 GetBottomRight() const { return mBottomRight; }
		float GetWidth() const { return mWidth; }
		float GetHeight() const { return mHeight; }

	protected:
		const Texture* mTexturePtr;
		glm::vec2 mTopLeft, mBottomRight;
		float mWidth, mHeight;
	};

	class GRAPHITE_API Animation2D : public Asset
	{
	public:
		Animation2D();
		~Animation2D();

		void Load(const rapidjson::Value& params);

	protected:
		std::vector<Frame2D> mFrames;
	};

}