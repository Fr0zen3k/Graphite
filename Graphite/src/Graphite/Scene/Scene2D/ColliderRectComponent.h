//
// Created by Mauricio Smit
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_COLLIDERRECTCOMPONENT_H
#define GRAPHITE_COLLIDERRECTCOMPONENT_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "../Component.h"

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

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif