//
// Created by Mauricio Smit
//
#include "Graphite/Core/grpch.h"

#pragma once

namespace Graphite
{
	class Entity;
	class ComponentFactory;

	class GRAPHITE_API Scene
	{
	public:

		struct NameTaken : std::runtime_error {
			inline NameTaken(std::string message) : std::runtime_error(message) {}
		};

		struct NonexistantEntity : std::runtime_error {
			inline NonexistantEntity(std::string message) : std::runtime_error(message) {}
		};


		Scene(ComponentFactory* componentFactory);
		virtual ~Scene();

		// Loads the scene from a json object
		void LoadFromJSON(const rapidjson::Value& root);

		// Returns the entity with the specified name. Returns nulptr if it doesn't exist
		Entity* getEntity(const std::string& name);

		// Creates an entity and adds it.
		Entity* createEntity(const std::vector<Component*>& components, const std::string& name = "");

		// Removes an entity and deletes it.
		void destroyEntity(Entity* e);

		virtual void onComponentAdded(Component* c);
		virtual void onComponentRemoved(Component* c);

	protected:
		ComponentFactory* mComponentFactoryPtr;
		std::set<std::unique_ptr<Entity>> mEntities;
		std::map<std::string, std::set<std::unique_ptr<Entity>>::iterator> mEntitiesByName;

		// Adds an existing entity to the scene. Takes ownership of it.
		// If an entity with the given name already exists in the scene, throws NameTaken
		void addEntity(Entity* e);

		// Removes an entity from the scene, without destroying it. Abandons ownership of it.
		// If an entity doesn't exist in the scene, throws NonexistantEntity
		void removeEntity(Entity* e);
	};
}