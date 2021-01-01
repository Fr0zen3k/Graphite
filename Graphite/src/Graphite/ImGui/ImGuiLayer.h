#if defined (_MSC_VER)
#pragma once
#pragma warning(disable: 4251)
#endif

#include "Graphite/Core/grpch.h"

#include "Graphite/Core/Core.h"

#include "Graphite/Core/Layer.h"



namespace Graphite
{

	class ImGuiLayer : public Layer
	{
		ImGuiLayer();
		ImGuiLayer(const std::string& name);
		~ImGuiLayer();

		void OnAttach() const override;
		void OnDetach() const override;
		void OnTick() const override;
		void OnEvent(Event& event) const override;
	};
	
}
