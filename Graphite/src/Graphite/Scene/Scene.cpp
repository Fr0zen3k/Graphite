#include "Scene.h"
#include "Entity.h"
#include "ComponentFactory.h"

namespace Graphite
{
	Scene::Scene(ComponentFactory* componentFactory)
		: mComponentFactoryPtr(componentFactory)
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::LoadFromJSON(const rapidjson::Value& root)
	{
		auto& jsonEntityList = root;

		for (auto& jsonEntity : jsonEntityList.GetArray())
		{
			// create components
			std::vector<Component*> newComps;
			newComps.reserve(jsonEntity["components"].Size());
			for (auto& jsonComponent : jsonEntity["components"].GetArray())
			{
				Component* newComp = mComponentFactoryPtr->GetNewComponent(jsonComponent);
				newComps.push_back(newComp);
			}

			// Create entity
			createEntity(newComps, jsonEntity["name"].GetString());
		}
	}

	Entity* Scene::getEntity(const std::string& name)
	{
		auto it = mEntitiesByName.find(name);

		if (it != mEntitiesByName.end())
		{
			return it->second->get();
		}

		return nullptr;
	}

	Entity* Scene::createEntity(const std::vector<Component*>& components, const std::string& name)
	{
		Entity* e = new Entity(components, this, name);
		addEntity(e);
	}

	void Scene::destroyEntity(Entity* e)
	{
		removeEntity(e);
		delete e;
	}

	void Scene::addEntity(Entity* e)
	{
		// Check
		auto it = mEntitiesByName.find(e->GetName());
		if (it != mEntitiesByName.end())
			throw NameTaken(std::string("Entity with name '") + e->GetName() + "' is already part of the scene");

		// add to sets
		auto itInsertedPair = mEntities.insert(std::make_unique<Entity>(e));
		mEntitiesByName.insert({ e->GetName(), itInsertedPair.first });

		// Specialization
		for (auto& tyCoPair : e->GetComponents())
		{
			onComponentAdded(tyCoPair.second);
		}
	}

	void Scene::removeEntity(Entity* e)
	{
		// Check
		auto it = mEntities.find(e);
		if (it == mEntities.end())
			throw NonexistantEntity("Entity doesn't exist");

		// Specialization
		for (auto& tyCoPair : e->GetComponents())
		{
			onComponentRemoved(tyCoPair.second);
		}
		onEntityRemoved(e);

		// Remove
		mEntities.erase(it);
		mEntitiesByName.erase(e->GetName());
	}

	void Scene::onComponentAdded(Component* c)
	{
	}

	void Scene::onComponentRemoved(Component* c)
	{
	}
}