#include "Graphite/Core/grpch.h"
#include "../Scene2D/Node2DComponent.h"
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

	void EventQueueComponent::post(const std::shared_ptr<ComponentEvent>& evPtr)
	{
		mEventQueue.emplace_back(evPtr);
	}

	void EventQueueComponent::processEvents()
	{
		while (mEventQueue.size() > 0)
		{
			// Get event and event type info
			const ComponentEvent* ev = mEventQueue.front().get();
			const std::type_info* evTypeId = &typeid(*ev);

			// Callbacks
			for (auto& callback : mCallbacksPerType[evTypeId])
			{
				callback.call(*ev);
			}

			// pop event
			mEventQueue.pop_front();
		}
	}

	void EventQueueComponent::registerCallback(const CallbackMethodWrapper& callback)
	{
		mCallbacksPerType[callback.GetEventTypeInfo()].push_back(callback);
	}
}