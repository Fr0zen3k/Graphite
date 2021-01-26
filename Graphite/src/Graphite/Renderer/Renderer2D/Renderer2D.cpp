#include "Graphite/Core/grpch.h"

#include "Renderer2D.h"

namespace Graphite
{

	GraphicsContext* Renderer2D::s_GraphicsContext;

	void Renderer2D::Init()
	{
		try
		{
			s_GraphicsContext = GraphicsContext::GetContext();
		}
		catch (std::runtime_error e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	
	void Renderer2D::Shutdown()
	{
		delete s_GraphicsContext;
	}

	GraphicsContext* Renderer2D::GetGraphicsContext()
	{
		return s_GraphicsContext;
	}

	
}