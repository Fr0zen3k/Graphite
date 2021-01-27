//
// Created by Jan Kresic on 9/19/20.
//

#include "Graphite/Core/grpch.h"

#include "Application.h"
//#include "Graphite/Renderer/Renderer2D/Renderer2D.h"

namespace Graphite {

    Application* Application::s_Instance = nullptr;
	
    Application::Application()
    {
        s_Instance = this;
    	
        m_Window = Window::grCreateWindow();
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    }

    Application::~Application()
    {
        //delete m_ActiveCamera;
        delete m_Window;
    }

    void Application::run() {
        while (true)
        {
            m_Window->Update();
//            Renderer2D::OnTick();
        }
    }

	void Application::OnEvent(Event& e)
	{
        //GR_CORE_LOG_TRACE("{0}", e.ToString());
        EventDispatch d(e);
        d.Dispatch<KeyDownEvent>([](KeyDownEvent e)
            {
                return true;
            });
	}

	//Camera* Application::GetActiveCameraInstance()
	//{
        //return m_ActiveCamera;
	//}


}