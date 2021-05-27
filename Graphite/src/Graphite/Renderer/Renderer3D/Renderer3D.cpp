#include "Graphite/Core/grpch.h"
#include "Renderer3D.h"

#include "Graphite/Renderer/RendererCore/Platform/Vulkan/VulkanRendererAPI.h"

namespace Graphite
{
	GraphicsContext* Renderer3D::s_GraphicsContext = nullptr;
	RendererSettings Renderer3D::s_Settings;
	
	void Renderer3D::Init()
	{
		try
		{
			s_GraphicsContext = GraphicsContext::GetContext();
		}
		catch (std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	void Renderer3D::InitAPI()
	{
		try
		{
			VulkanRendererAPI::Init();
		}
		catch (std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	void Renderer3D::OnTick()
	{
		int i = VulkanRendererAPI::StartDrawing();

		// for every gameobject, if in frustum and culling is enabled, draw appropriate lod or max lod if lod management is disabled
		
		VulkanRendererAPI::EndDrawing(i);
	}

	void Renderer3D::Shutdown()
	{
		VulkanRendererAPI::Shutdown();
		delete s_GraphicsContext;
	}

	void Renderer3D::UpdateSettings(RendererSettings settings)
	{
		s_Settings = settings;
	}

	GraphicsContext* Renderer3D::GetGraphicsContext()
	{
		return s_GraphicsContext;
	}
}
