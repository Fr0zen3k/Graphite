#include "Entity.h"

namespace Graphite
{
	Entity::Entity(const std::vector<ComponentContainer>& components)
	{
		for (auto& compCont : components)
		{
			mComponents.insert({ compCont.typeInfoPtr(), compCont.componentPtr() });
		}
	}
}