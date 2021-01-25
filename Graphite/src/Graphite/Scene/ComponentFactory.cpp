#include "Graphite/Core/grpch.h"
#include "ComponentFactory.h"
#include "Scene2D/Node2DComponent.h"
#include "Scene2D/ColliderRectComponent.h"
#include "Scene2D/RigidBody2DComponent.h"
#include "SharedComponents/EventQueueComponent.h"

namespace Graphite
{
	ComponentFactory& ComponentFactory::instance()
	{
		static ComponentFactory in;
		return in;
	}

	ComponentFactory::ComponentFactory()
	{
		RegisterConstructor("Node2D", 
			[](const rapidjson::Value& val, Scene* scene) {return new Node2DComponent(val, scene); }
		);
		RegisterConstructor("ColliderRect", 
			[](const rapidjson::Value& val, Scene* scene) {return new ColliderRectComponent(val); }
		);
		RegisterConstructor("RigidBody2D", 
			[](const rapidjson::Value& val, Scene* scene) {return new RigidBody2DComponent(val); }
		);
		RegisterConstructor("EventQueue", 
			[](const rapidjson::Value& val, Scene* scene) {return new EventQueueComponent(val); }
		);
	}

	Component* ComponentFactory::GetNewComponent(const rapidjson::Value& obj, Scene* scene)
	{
		std::string typeName = obj["type"].GetString();
		auto it = mConstructorsPerType.find(typeName);

		if (it == mConstructorsPerType.end())
		{
			throw std::invalid_argument(std::string("No Component constructor for type '") + typeName + "'");
		}

		return mConstructorsPerType[typeName](obj, scene);
	}

	void ComponentFactory::RegisterConstructor(const std::string& typeName, ComponentConstructor ctor)
	{
		mConstructorsPerType[typeName] = ctor;
	}
}