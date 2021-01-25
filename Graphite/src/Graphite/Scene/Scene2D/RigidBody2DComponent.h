//
// Created by Mauricio Smit
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_RIGIDBODY2DCOMPONENT_H
#define GRAPHITE_RIGIDBODY2DCOMPONENT_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "../Component.h"

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

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif