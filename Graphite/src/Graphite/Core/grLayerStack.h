#pragma once

#ifndef GRAPHITE_LAYERSTACK_H
#define GRAPHITE_LAYERSTACK_H

#include "Graphite/Core/grpch.h"

#include "Graphite/Core/Core.h"

#include "Graphite/EventCore/grEvents.h"
#include "grLayer.h"

namespace Graphite
{

	class grLayerStack
	{
	public:
		grLayerStack();
		~grLayerStack();
		
		void AttachLayer(grLayer* layer);
		void DetachLayer(grLayer* layer);
		void AttachOverlay(grLayer* layer);
		void DetachOvarlay(grLayer* layer);

		void OnEvent(grEvent& event);
		void Tick();
		
		private:
		std::vector<grLayer*> m_Layers;
		std::vector<grLayer*> m_Overlays;
	};

}

#endif
