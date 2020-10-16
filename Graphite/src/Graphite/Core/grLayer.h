#pragma once

#ifndef GRAPHITE_LAYER_H
#define GRAPHITE_LAYER_H

#include "Graphite/Core/grpch.h"

#include "Graphite/Core/Core.h"

#include "Graphite/EventCore/grEvents.h"

namespace Graphite
{

	class grLayer
	{
	public:
		grLayer();
		grLayer(const std::string& name);
		~grLayer();

		virtual void OnAttach() const = 0;
		virtual void OnDetach() const = 0;
		virtual void OnTick() const = 0;
		virtual void OnEvent(grEvent& event) const = 0;

		inline const std::string& GetName() const { return m_Name; }

	protected:
		std::string m_Name;
	};
	
}

#endif