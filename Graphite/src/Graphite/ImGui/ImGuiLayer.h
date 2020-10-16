
#include "Graphite/Core/grpch.h"

#include "Graphite/Core/Core.h"

#include "Graphite/Core/grLayer.h"



namespace Graphite
{

	class ImGuiLayer : public grLayer
	{
		ImGuiLayer();
		ImGuiLayer(const std::string& name);
		~ImGuiLayer();

		void OnAttach() const override;
		void OnDetach() const override;
		void OnTick() const override;
		void OnEvent(grEvent& event) const override;
	};
	
}
