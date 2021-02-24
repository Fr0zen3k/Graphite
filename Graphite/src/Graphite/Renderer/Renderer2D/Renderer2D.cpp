#include "Graphite/Core/grpch.h"

#include "Renderer2D.h"
#include "../RendererCore/Platform/Vulkan/VulkanRendererAPI.h"

#include "../RendererCore/MeshCore/Quad.h"
#include "../RendererCore/MeshCore/Line.h"
#include "../RendererCore/MeshCore/Point.h"

#include "glm/glm.hpp"

namespace Graphite
{

	GraphicsContext* Renderer2D::s_GraphicsContext = nullptr;


	// ---------------------- TEST -----------------------
	Quad* Renderer2D::s_TestQuad = nullptr;
	Math::Transform* Renderer2D::s_TestTransform = new Math::Transform({ 5.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
	Texture* Renderer2D::s_TestTexture = nullptr;
	// ---------------------- TEST -----------------------
	
	
	void Renderer2D::Init()
	{
		try
		{
			Point::Init();
			Line::Init();
			Quad::Init();
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
		VulkanRendererAPI::Draw(i);
		VulkanRendererAPI::EndDrawing(i);
	}

	
	void Renderer2D::Shutdown()
	{
		VulkanRendererAPI::Shutdown();
		delete s_TestQuad;
		delete s_TestTransform;
		delete s_TestTexture;
		delete s_GraphicsContext;
	}

	GraphicsContext* Renderer2D::GetGraphicsContext()
	{
		return s_GraphicsContext;
	}

	
}