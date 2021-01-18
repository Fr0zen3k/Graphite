//
// Created by Mauricio Smit
//
#include "Graphite/Core/grpch.h"

#pragma once

#include "../Component.h"
//#include "AbstractCollider2DComponent.h"

#include "glm/glm.hpp"

namespace Graphite
{

	class GRAPHITE_API ColliderRectComponent : public Component
	{
	public:
		ColliderRectComponent(float width, float height);
		ColliderRectComponent(const rapidjson::Value& params);
		~ColliderRectComponent();

		float GetWidth() const { return mWidth; }
		float GetHeight() const { return mHeight; }

		// Returns the rect's vertices, transformed by the matrix
		std::array<glm::vec2, 4> GetTransformedVertices(const glm::mat4x4& transform);

	protected:
		float mWidth, mHeight;
	};

}