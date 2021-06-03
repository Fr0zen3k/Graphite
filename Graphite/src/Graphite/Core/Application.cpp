//
// Created by Jan Kresic on 9/19/20.
//

#include "Graphite/Core/grpch.h"

#include "Application.h"

#include "Input.h"
#include "Graphite/Renderer/Renderer3D/Renderer3D.h"


#include "glm/gtx/string_cast.hpp"

namespace Graphite {

    Application* Application::s_Instance = nullptr;

    std::string Application::s_ApplicationDirectory = "";
	
    Application::Application()
    {
        s_Instance = this;
    	
        m_Window = Window::grCreateWindow();
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    }

    Application::~Application()
    {
        delete m_ActiveCamera;
        delete m_Window;
    }

    void Application::run() {
        while (true)
        {
            m_Window->Update();

            Tick();
        	
            Renderer3D::OnTick();

        	// -------------------------- TEST --------------------------------
        	if(Input::IsKeyPressed(GR_KEY_A))
        	{
                m_ActiveCamera->Translate(m_ActiveCamera->GetPosition() + glm::vec3(-0.001f, 0.0f, 0.0f));
        	}

            if(Input::IsKeyPressed(GR_KEY_SPACE) && Input::IsKeyPressed(GR_KEY_S))
            {
                m_ActiveCamera->Translate(m_ActiveCamera->GetPosition() + glm::vec3(0.0f, -0.001f, 0.0f));
            }
        	else if(Input::IsKeyPressed(GR_KEY_S))
        	{
                m_ActiveCamera->Translate(m_ActiveCamera->GetPosition() + glm::vec3(0.0f, 0.0f, 0.001f));
        	}

        	if(Input::IsKeyPressed(GR_KEY_SPACE) && Input::IsKeyPressed(GR_KEY_W))
        	{
                m_ActiveCamera->Translate(m_ActiveCamera->GetPosition() + glm::vec3(0.0f, 0.001f, 0.0f));
        	}
            else if (Input::IsKeyPressed(GR_KEY_W))
            {
                m_ActiveCamera->Translate(m_ActiveCamera->GetPosition() + glm::vec3(0.0f, 0.0f, -0.001f));
            }

            if (Input::IsKeyPressed(GR_KEY_D))
            {
                m_ActiveCamera->Translate(m_ActiveCamera->GetPosition() + glm::vec3(0.001f, 0.0f, 0.0f));
            }        	
            // -------------------------- TEST --------------------------------
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

	Camera* Application::GetActiveCameraInstance()
	{
       return m_ActiveCamera;
	}


}