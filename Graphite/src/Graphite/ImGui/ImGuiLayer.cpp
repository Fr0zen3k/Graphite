#include "Graphite/Core/grpch.h"
#include "ImGuiLayer.h"

namespace Graphite
{
	ImGuiLayer::ImGuiLayer(): grLayer() {}

	ImGuiLayer::ImGuiLayer(const std::string& name): grLayer(name) {}

	ImGuiLayer::~ImGuiLayer() {}

	void ImGuiLayer::OnAttach() const
	{
		
	}
	
	void ImGuiLayer::OnDetach() const
	{
		
	}
	void ImGuiLayer::OnTick() const
	{
		
	}
	
	void ImGuiLayer::OnEvent(grEvent& event) const
	{
		
	}

}
