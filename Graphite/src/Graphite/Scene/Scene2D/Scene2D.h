//
// Created by Mauricio Smit
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_SCENE2D_H
#define GRAPHITE_SCENE2D_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "Graphite/Scene/Scene.h"

#include "Node2DComponent.h"

namespace Graphite
{
	class GRAPHITE_API Scene2D : public Scene
	{
	public:

		Scene2D();
		~Scene2D();

		Node2DComponent* GetRootNode();

	protected:
		std::set<Node2DComponent*> mEntities;

		void onComponentAdded(Component* c);
		void onComponentRemoved(Component* c);
	};
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif