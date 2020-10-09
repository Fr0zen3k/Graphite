//
// Created by Jan Kresic on 9/19/20.
//

#include "Graphite/Core/grpch.h"

#include "Application.h"

namespace Graphite {

    Application* Application::s_Instance = nullptr;
	
    Application::Application()
    {
        s_Instance = this;
    	
        m_Window = std::unique_ptr<grWindow>(grWindow::grCreateWindow());
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    }

    Application::~Application() {}

    void Application::run() {
        while (true)
        {
            m_Window->Update();
        }
    }

	void Application::OnEvent(grEvent& e)
	{
        GR_CORE_LOG_TRACE("{0}", e.ToString());
        grEventDispatch d(e);
        d.Dispatch<grKeyDownEvent>([](grKeyDownEvent e)
            {
                return true;
            });
	}

}