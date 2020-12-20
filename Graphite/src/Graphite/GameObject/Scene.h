//
// Created by Mauricio Smit
//
#include "Graphite/Core/grpch.h"

#pragma once

#include "Entity.h"

namespace Graphite
{
	class GRAPHITE_API Scene
	{
	public:
		Scene(const std::string& filename);
		virtual ~Scene() = 0;

		Entity* createEntity(const std::vector<ComponentContainer>& components);
		Entity* createNode2DEntity(const std::vector<ComponentContainer>& components);

	private:
		std::set<std::unique_ptr<Component>> mEntities;
	};
}