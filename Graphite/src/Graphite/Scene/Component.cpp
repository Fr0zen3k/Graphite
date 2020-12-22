#include "Component.h"

namespace Graphite
{

	Component::Component():
		mEntity(nullptr)
	{
	}

	void Component::SetEntity(Entity* e)
	{
		mEntity = e;
	}

	void Component::Init()
	{

	}

}