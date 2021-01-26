//
// Created by Mauricio Smit on 12/21/20
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_EVENTQUEUECOMPONENT_H
#define GRAPHITE_EVENTQUEUECOMPONENT_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "../Component.h"


namespace Graphite
{

	struct GRAPHITE_API ComponentEvent
	{
		virtual ~ComponentEvent() {};
		int a;
	};

	/*
	Used to wrap event handler callback methods for specialized events
	(abstract and non-specialized: use CallbackMethodWrapper with
	the appropriate template types for the wrapped method)
	*/
	class GRAPHITE_API CallbackMethodWrapper
	{
	public:

		CallbackMethodWrapper(void* ownerPtr, const std::type_info* typeInfo, std::function<void(void*, const ComponentEvent&)> method)
			: ownerPtr(ownerPtr)
			, typeInfo(typeInfo)
			, caller(method)
		{
			
		}

		// calls the wrapped method, with the specified event.
		// Make sure the event can be casted to the appropriate type for the specified method
		virtual void call(const ComponentEvent& event)
		{
			caller(ownerPtr, event);
		}

		// Returns the pointer to the type_info of the appropriate ComponentEvent type for the wrapped method
		virtual const std::type_info* GetEventTypeInfo() const
		{
			return typeInfo;
		}

		// Returns a newly constructed object, of identical type as the actual type of this object
		//virtual AbstractCallbackMethodWrapper* newClone() const = 0;

	private:
		void* ownerPtr;
		const std::type_info* typeInfo;
		std::function<void(void*, const ComponentEvent&)> caller;
	};

	/*
	Used to wrap event handler callback methods for specialized events.

	ownerPtr is the owner object of the method
	method is the method of the object that will be called
	*/
	/*template<class _OwnerT, class _EvT>
	struct GRAPHITE_API CallbackMethodWrapper : public AbstractCallbackMethodWrapper
	{
		static_assert(std::is_base_of<ComponentEvent, _EvT>::value, "CallbackMethodWrapper only wraps ComponentEvent handlers.");

		_OwnerT* ownerPtr;
		std::function<void(_OwnerT*, const _EvT&)> method;

		CallbackMethodWrapper(_OwnerT* ownerPtr, std::function<void(_OwnerT*, const _EvT&)> method)
			: ownerPtr(ownerPtr)
			, method(method)
		{}
		CallbackMethodWrapper() = delete;

		// calls the wrapped method, with the specified event.
		// Make sure the event can be casted to the appropriate type for the specified method
		void call(const ComponentEvent& ev)
		{
			const _EvT* der = dynamic_cast<const _EvT*>(&ev);
			if (der == nullptr)
			{
				throw std::invalid_argument(
					std::string("Event must be of type ") + typeid(_EvT).name() + "!"
				);
			}

			return method(ownerPtr, *der);
		}

		// Returns the pointer to the type_info of the appropriate ComponentEvent type for the wrapped method
		const std::type_info* GetEventTypeInfo() const
		{
			return &typeid(_EvT);
		}

		// Returns a newly constructed object, of identical type as the actual type of this object
		AbstractCallbackMethodWrapper* newClone() const
		{
			return new CallbackMethodWrapper<_OwnerT, _EvT>(*this);
		}

	};*/

	class GRAPHITE_API EventQueueComponent : public Component
	{
	public:
		EventQueueComponent();
		EventQueueComponent(const rapidjson::Value& params);
		~EventQueueComponent();

		void post(const std::shared_ptr<ComponentEvent>& evPtr);

		template<class _EvT>
		void post(_EvT* ev)
		{
			post(std::shared_ptr<_EvT>(ev));
		}

		void processEvents();

		/*
		Registers the callback method by the wrapper that will be called
		when the event that can be passed to the wrapped method is processed.
		*/
		void registerCallback(const CallbackMethodWrapper& callback);

		/*
		Registers the callback method that will be called when the event that can be passed
		to the wrapped method is processed.

		EXAMPLE: evQueueComp.registerCallback(this, onUpdate), if the onUpdate
		method of this object can process ComponentUpdateEvent, it will be called after
		ComponentEvent is posted to the queue and processed.
		*/
		template<class _OwnerT, class _EvT>
		void registerCallback(_OwnerT* ownerPtr, void(_OwnerT::*method)(const _EvT&) )//std::function<void(_OwnerT*, const _EvT&)>
		{
			auto callerFunction = [](void* owner, const ComponentEvent& ev, std::function<void(_OwnerT*, const _EvT&)> method)
			{
				method((_OwnerT*)owner, (const _EvT&)ev);
			};
			auto caller = std::bind(callerFunction, std::placeholders::_1, std::placeholders::_2, method);

			auto c = CallbackMethodWrapper(ownerPtr, &typeid(_EvT), caller);
			registerCallback(c);
		}
		
	protected:
		std::map<const std::type_info*, std::vector<CallbackMethodWrapper>> mCallbacksPerType;
		std::deque<std::shared_ptr<ComponentEvent>> mEventQueue;
	};


	struct GRAPHITE_API ComponentUpdateEvent : public ComponentEvent
	{
		// seconds since last update
		float sElapsed;
	};

	struct GRAPHITE_API ComponentCollidedEvent : public ComponentEvent
	{
		// the entity we touched
		Entity* other;

		// index of the collision material
		size_t materialIndex;
	};

}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif