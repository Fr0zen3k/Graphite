//
// Created by Mauricio Smit
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_ABSTRACTBEHAVIOURCOMPONENT_H
#define GRAPHITE_ABSTRACTBEHAVIOURCOMPONENT_H

#include "Graphite/Core/grpch.h"
#include "Graphite/Core/Core.h"

#include "../Component.h"
#include "EventQueueComponent.h"

namespace Graphite
{
	/*
	This is really just a component that by default registers a few callback functions
	for common events. Maybe should be removed as it reminds me of the blob pattern.
	*/
	class GRAPHITE_API AbstractBehaviorComponent : public Component
	{
	public:
		AbstractBehaviorComponent();
		~AbstractBehaviorComponent() = 0;

		void Init();

		void onUpdate(const ComponentUpdateEvent& ev);
		void onCollision(const ComponentCollidedEvent& ev);


	protected:
	};

}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif