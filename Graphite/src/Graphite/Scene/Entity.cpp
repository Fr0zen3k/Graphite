#include "Entity.h"
#include "Component.h"

namespace Graphite
{
	Entity::Entity(const std::vector<Component*>& components, Scene* scene, const std::string& name)
		: mName(name)
		, mScenePtr(scene)
	{
		// the components that we add right now
		std::vector<Component*> startingComponents = components;

		// add components
		for (auto& compPtr : components)
		{
			mComponents.insert(
				{ 
					&typeid(*compPtr),
					std::unique_ptr<Component>(compPtr)
				}
			);
			compPtr->SetEntity(this);
		}

		// Perform init only on added components,
		// since new components could be added and inited by dependency during the init process
		for (auto compPtr : startingComponents)
		{
			compPtr->Init();
		}
	}

	Entity::~Entity()
	{
	}
}