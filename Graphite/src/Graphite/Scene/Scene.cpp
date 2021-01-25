#include "Graphite/Core/grpch.h"
#include "Scene.h"
#include "Entity.h"
#include "ComponentFactory.h"

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
		rapidjson::Document d;
		d.ParseStream(source);

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
		Entity* e = new Entity(components, this, name);
		addEntity(e);
	}

	void Scene::DestroyEntity(Entity* e)
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
			onComponentAdded(tyCoPair.second.get());
		}
	}

	void Scene::removeEntity(Entity* e)
	{
		// Check
		auto it = std::find_if(mEntities.begin(), mEntities.end(), [&](std::unique_ptr<Entity>& p) { return p.get() == e; });
		//auto it = mEntities.find(e);
		if (it == mEntities.end())
			throw NonexistantEntity("Entity doesn't exist");

		// Specialization
		for (auto& tyCoPair : e->GetComponents())
		{
			onComponentRemoved(tyCoPair.second.get());
		}

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