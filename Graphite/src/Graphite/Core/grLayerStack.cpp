#include "Graphite/Core/grpch.h"

#include "grLayerStack.h"

namespace Graphite
{

	grLayerStack::grLayerStack() {}
	
	grLayerStack::~grLayerStack()
	{
		for(auto layer : m_Layers)
		{
			delete layer;
		}
		for(auto layer : m_Overlays)
		{
			delete layer;
		}
	}

	void grLayerStack::AttachLayer(grLayer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}
	void grLayerStack::DetachLayer(grLayer* layer)
	{
		auto target = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (target != m_Layers.end())
		{
			m_Layers.erase(target);
		}

		layer->OnDetach();
	}
	void grLayerStack::AttachOverlay(grLayer* layer)
	{
		m_Overlays.emplace_back(layer);
		layer->OnAttach();
	}
	void grLayerStack::DetachOvarlay(grLayer* layer)
	{
		auto target = std::find(m_Overlays.begin(), m_Overlays.end(), layer);

		if (target != m_Overlays.end())
		{
			m_Overlays.erase(target);
		}
		layer->OnDetach();
	}

	void grLayerStack::OnEvent(grEvent& event)
	{
		for (auto it = m_Overlays.end(); it != m_Overlays.begin(); )
		{
			(*--it)->OnEvent(event);
			if(event.isHandled())
			{
				return;
			}
		}
		for (auto it = m_Layers.end(); it != m_Layers.begin(); )
		{
			(*--it)->OnEvent(event);
			if (event.isHandled())
			{
				return;
			}
		}
	}
	
	void grLayerStack::Tick()
	{
		for(auto layer : m_Layers)
		{
			layer->OnTick();
		}
		for(auto layer : m_Overlays)
		{
			layer->OnTick();
		}
	}
	
}
