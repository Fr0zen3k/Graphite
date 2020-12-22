//
// Created by Mauricio Smit
//
#include "Graphite/Core/grpch.h"

#pragma once

#include "../Component.h"
#include "EventQueueComponent.h"

#include <set>

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