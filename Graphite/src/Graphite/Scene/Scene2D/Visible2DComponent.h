//
// Created by Mauricio Smit
//
#include "Graphite/Core/grpch.h"

#pragma once

#include "../Component.h"
#include "AbstractCollider2DComponent.h"

#include "glm/glm.hpp"

namespace Graphite
{
	class Animation2D;

	class GRAPHITE_API Visible2DComponent : public Component
	{
	public:
		Visible2DComponent();
		Visible2DComponent(const rapidjson::Value& params);
		~Visible2DComponent();



	protected:
	};

}