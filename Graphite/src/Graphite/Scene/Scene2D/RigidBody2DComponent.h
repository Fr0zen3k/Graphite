//
// Created by Mauricio Smit
//
#pragma once

#include "Graphite/Core/grpch.h"

#include "../Component.h"
#include "AbstractCollider2DComponent.h"

#include "glm/glm.hpp"

namespace Graphite
{

	class GRAPHITE_API RigidBody2DComponent : public Component
	{
	public:
		RigidBody2DComponent();
		RigidBody2DComponent(const rapidjson::Value& params);
		~RigidBody2DComponent();

	protected:
	};

}