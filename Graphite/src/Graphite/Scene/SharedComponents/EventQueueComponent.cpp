#include "Node2DComponent.h"
#include "EventQueueComponent.h"

namespace Graphite
{
	EventQueueComponent::EventQueueComponent()
	{
	}

	EventQueueComponent::EventQueueComponent(const rapidjson::Value& params)
	{
	}

	EventQueueComponent::~EventQueueComponent()
	{
	}

	void EventQueueComponent::post(ComponentEvent* ev)
	{
		mEventQueue.push_back(ev);
	}

	void EventQueueComponent::processEvents()
	{
		while (mEventQueue.size() > 0)
		{
			// Get event and event type info
			ComponentEvent* ev = mEventQueue.front();
			const std::type_info* evTypeId = typeid(*ev);

			// Callbacks
			for (auto& callbackPtr : mCallbacksPerType[evTypeId])
			{
				callbackPtr->call(*ev);
			}

			// pop event
			mEventQueue.pop_front();
		}
	}

	void EventQueueComponent::registerCallback(const AbstractCallbackMethodWrapper& callback)
	{
		mCallbacksPerType[callback.GetEventTypeInfo()].insert(callback.newClone());
	}
}