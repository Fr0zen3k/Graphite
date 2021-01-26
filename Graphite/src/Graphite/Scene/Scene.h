//
// Created by Mauricio Smit
//

#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_SCENE_H
#define GRAPHITE_SCENE_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "Component.h"
#include "Graphite/Assets/Asset.h"

namespace Graphite
{
	class Entity;

	class GRAPHITE_API Scene : public Asset
	{
	public:

		struct NameTaken : std::runtime_error {
			inline NameTaken(std::string message) : std::runtime_error(message) {}
		};

		struct NonexistantEntity : std::runtime_error {
			inline NonexistantEntity(std::string message) : std::runtime_error(message) {}
		};


		Scene();
		virtual ~Scene();

		// Loads the scene from a json object
		void Load(std::istream& source);
		void Load(const rapidjson::Value& root);
		void Unload();

		virtual void Update(float sElapsed);

		// Returns the entity with the specified name. Returns nulptr if it doesn't exist
		Entity* GetEntity(const std::string& name);

		// Creates an entity and adds it.
		Entity* CreateEntity(const std::vector<Component*>& components, const std::string& name = "");

		// Removes an entity and deletes it.
		void DestroyEntity(Entity* e);

		virtual void onComponentAdded(Component* c);
		virtual void onComponentRemoved(Component* c);

	protected:
		std::set<std::shared_ptr<Entity>> mEntities;
		std::map<std::string, std::set<std::shared_ptr<Entity>>::iterator> mEntitiesByName;

		// Adds an existing entity to the scene. Takes ownership of it.
		// If an entity with the given name already exists in the scene, throws NameTaken
		void addEntity(Entity* e);

		// Removes an entity from the scene, without destroying it. Abandons ownership of it.
		// If an entity doesn't exist in the scene, throws NonexistantEntity
		void removeEntity(Entity* e);
	};
}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif