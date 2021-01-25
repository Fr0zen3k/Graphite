#include "AbstractBehaviorComponent.h"

namespace Graphite
{
	AbstractBehaviorComponent::AbstractBehaviorComponent()
	{
	}

	AbstractBehaviorComponent::~AbstractBehaviorComponent()
	{
	}

	void AbstractBehaviorComponent::Init()
	{
		auto evQ = &CompReq<EventQueueComponent>();

		evQ->registerCallback(this, &onUpdate);
		evQ->registerCallback(this, &onCollision);
	}

	void AbstractBehaviorComponent::onUpdate(const ComponentUpdateEvent& ev)
	{

	}

	void AbstractBehaviorComponent::onCollision(const ComponentCollidedEvent& ev)
	{

	}
}