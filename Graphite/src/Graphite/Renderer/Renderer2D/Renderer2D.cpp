#include "Graphite/Core/grpch.h"

#include "Renderer2D.h"
#include "../RendererCore/Platform/Vulkan/VulkanRendererAPI.h"
#include "Graphite/Assets/Material.h"

#include "glm/glm.hpp"

namespace Graphite
{

	GraphicsContext* Renderer2D::s_GraphicsContext = nullptr;
	
	
	void Renderer2D::Init()
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

	void Renderer2D::InitAPI()
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

	void Renderer2D::OnTick()
	{	
		int i = VulkanRendererAPI::StartDrawing();
		VulkanRendererAPI::Draw(i, nullptr, nullptr, nullptr, glm::mat4(1.0f), Material());
		VulkanRendererAPI::EndDrawing(i);
	}

	
	void Renderer2D::Shutdown()
	{
		VulkanRendererAPI::Shutdown();
		delete s_GraphicsContext;
	}

	GraphicsContext* Renderer2D::GetGraphicsContext()
	{
		return s_GraphicsContext;
	}

	
}