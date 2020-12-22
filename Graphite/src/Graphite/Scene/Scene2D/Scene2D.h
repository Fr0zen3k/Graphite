//
// Created by Mauricio Smit
//
#include "Graphite/Core/grpch.h"

#pragma once

#include "Graphite/Scene/Scene.h"

namespace Graphite
{
	class Node2DComponent;
	class AbstractCollidableComponent;

	class GRAPHITE_API Scene2D : Scene
	{
	public:

		Scene2D();
		Scene2D(rapidjson::Value root);
		~Scene2D();

		Node2DComponent* GetRootNode();

	protected:
		std::set<Node2DComponent*> mEntities;
		std::set<Node2DComponent*> mEntities;

		void onComponentAdded(Component* c);
		void onComponentRemoved(Component* c);
	};
}