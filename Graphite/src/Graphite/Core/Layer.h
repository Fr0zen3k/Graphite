#if defined (_MSC_VER)
#pragma once
#pragma warning(disable: 4251)
#endif

#ifndef GRAPHITE_LAYER_H
#define GRAPHITE_LAYER_H

#include "Graphite/Core/grpch.h"

#include "Graphite/Core/Core.h"

#include "Graphite/EventCore/Events.h"

namespace Graphite
{

	class Layer
	{
	public:
		Layer();
		Layer(const std::string& name);
		~Layer();

		virtual void OnAttach() const = 0;
		virtual void OnDetach() const = 0;
		virtual void OnTick() const = 0;
		virtual void OnEvent(Event& event) const = 0;

		inline const std::string& GetName() const { return m_Name; }

	protected:
		std::string m_Name;
	};
	
}

#endif