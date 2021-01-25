#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_LAYERSTACK_H
#define GRAPHITE_LAYERSTACK_H

#include "Graphite/Core/grpch.h"

#include "Graphite/Core/Core.h"

#include "Graphite/EventCore/Events.h"
#include "Layer.h"

namespace Graphite
{

	class GRAPHITE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		
		void AttachLayer(Layer* layer);
		void DetachLayer(Layer* layer);
		void AttachOverlay(Layer* layer);
		void DetachOvarlay(Layer* layer);

		void OnEvent(Event& event);
		void Tick();
		
		private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*> m_Overlays;
	};

}

#endif

#if defined (_MSC_VER)
#pragma warning(pop)
#endif