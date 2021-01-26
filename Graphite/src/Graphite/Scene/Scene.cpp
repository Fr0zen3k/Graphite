#include "Graphite/Core/grpch.h"
#include "Scene.h"
#include "Entity.h"
#include "ComponentFactory.h"
#include <rapidjson/istreamwrapper.h>

namespace Graphite
{
	Scene::Scene() :
		Asset(false)
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::Load(std::istream& source)
	{
		rapidjson::IStreamWrapper jsonStream(source);
		rapidjson::Document d;
		d.ParseStream(jsonStream);

		Load(d);
	}

	void Scene::Load(const rapidjson::Value& root)
	{
		auto& jsonEntityList = root;

		for (auto& jsonEntity : jsonEntityList.GetArray())
		{
			// create components
			std::vector<Component*> newComps;
			newComps.reserve(jsonEntity["components"].Size());
			for (auto& jsonComponent : jsonEntity["components"].GetArray())
			{
				Component* newComp = ComponentFactory::instance().GetNewComponent(jsonComponent, this);
				newComps.push_back(newComp);
			}

			// Create entity
			CreateEntity(newComps, jsonEntity["name"].GetString());
		}
	}

	void Scene::Unload()
	{
	}

	Entity* Scene::GetEntity(const std::string& name)
	{
		auto it = mEntitiesByName.find(name);

		if (it != mEntitiesByName.end())
		{
			return it->second->get();
		}

		return nullptr;
	}

	Entity* Scene::CreateEntity(const std::vector<Component*>& components, const std::string& name)
	{
		Entity* ePtr = new Entity(components, this, name);
		addEntity(ePtr);
		return ePtr;
	}

	void Scene::DestroyEntity(Entity* ePtr)
	{
		removeEntity(ePtr);
		delete ePtr;
	}

	void Scene::addEntity(Entity* ePtr)
	{
		// Check
		auto it = mEntitiesByName.find(ePtr->GetName());
		if (it != mEntitiesByName.end())
			throw NameTaken(std::string("Entity with name '") + ePtr->GetName() + "' is already part of the scene");

		// add to sets
		auto itInsertedPair = mEntities.insert(std::shared_ptr<Entity>(ePtr));
		mEntitiesByName.insert({ ePtr->GetName(), itInsertedPair.first });

		// Specialization
		for (auto& tyCoPair : ePtr->GetComponents())
		{
			onComponentAdded(tyCoPair.second.get());
		}
	}

	void Scene::removeEntity(Entity* ePtr)
	{
		// Check
		auto it = std::find_if(mEntities.begin(), mEntities.end(), [&](const std::shared_ptr<Entity>& p) { return p.get() == ePtr; });
		//auto it = mEntities.find(ePtr);
		if (it == mEntities.end())
			throw NonexistantEntity("Entity doesn't exist");

		// Specialization
		for (auto& tyCoPair : ePtr->GetComponents())
		{
			onComponentRemoved(tyCoPair.second.get());
		}

		// Remove
		mEntities.erase(it);
		mEntitiesByName.erase(ePtr->GetName());
	}

	void Scene::onComponentAdded(Component* c)
	{
	}

	void Scene::onComponentRemoved(Component* c)
	{
	}
}