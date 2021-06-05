//
// Created by Jan Kresic on 9/19/20.
//

#include "Graphite/Core/grpch.h"

#include "Application.h"

#include "Input.h"
#include "Graphite/Renderer/Renderer3D/Renderer3D.h"

#include "Utilities.h"

#include "glm/gtx/string_cast.hpp"

namespace Graphite {

    Application* Application::s_Instance = nullptr;

    std::string Application::s_ApplicationDirectory = "";

    Benchmarker* Application::s_Benchmarker = nullptr;

    std::chrono::high_resolution_clock::time_point Application::s_CurrentTick;
    std::chrono::high_resolution_clock::time_point Application::s_LastTick;
	
    Application::Application()
    {
        s_Instance = this;
    	
        m_Window = Window::grCreateWindow();
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        s_CurrentTick = std::chrono::high_resolution_clock::now();
        s_LastTick = std::chrono::high_resolution_clock::now();
    }

    Application::~Application()
    {
        delete m_ActiveCamera;
        delete m_Window;
    }

    void Application::SetAppDir(const std::string& path)
    {
        std::vector<std::string> purePath = Datamanip::SplitPath(path);

        std::stringstream ss;
    	
    	for(int i = 0; i < purePath.size(); i++)
    	{
            ss << purePath[i];
            ss << '\\';
    	}

        s_ApplicationDirectory = ss.str();
    }

    double Application::DeltaTime()
    {
        std::chrono::duration<double> delta = std::chrono::duration_cast<std::chrono::duration<double>>(s_CurrentTick - s_LastTick);

        return delta.count();
    }

    void Application::Run() {
        while (true)
        {
            s_CurrentTick = std::chrono::high_resolution_clock::now();
        	
            m_Window->Update();

            Tick();
        	
            Renderer3D::OnTick();


        	
        	// -------------------------- TEST --------------------------------
            s_Benchmarker->SetFrameTime(DeltaTime());
            s_Benchmarker->SetFPS(1.0 / DeltaTime());
            s_Benchmarker->SetLOD(Renderer3D::GetLOD());
            s_Benchmarker->SetVFC(Renderer3D::GetCulling());

            s_Benchmarker->Log();
        	
        	if(Input::IsKeyPressed(GR_KEY_A))
        	{
                m_ActiveCamera->Translate(m_ActiveCamera->GetPosition() + glm::vec3(-0.01f, 0.0f, 0.0f));
        	}

            if(Input::IsKeyPressed(GR_KEY_SPACE) && Input::IsKeyPressed(GR_KEY_S))
            {
                m_ActiveCamera->Translate(m_ActiveCamera->GetPosition() + glm::vec3(0.0f, -0.01f, 0.0f));
            }
        	else if(Input::IsKeyPressed(GR_KEY_S))
        	{
                m_ActiveCamera->Translate(m_ActiveCamera->GetPosition() + glm::vec3(0.0f, 0.0f, 0.01f));
        	}

        	if(Input::IsKeyPressed(GR_KEY_SPACE) && Input::IsKeyPressed(GR_KEY_W))
        	{
                m_ActiveCamera->Translate(m_ActiveCamera->GetPosition() + glm::vec3(0.0f, 0.01f, 0.0f));
        	}
            else if(Input::IsKeyPressed(GR_KEY_W))
            {
                m_ActiveCamera->Translate(m_ActiveCamera->GetPosition() + glm::vec3(0.0f, 0.0f, -0.01f));
            }

            if(Input::IsKeyPressed(GR_KEY_D))
            {
                m_ActiveCamera->Translate(m_ActiveCamera->GetPosition() + glm::vec3(0.01f, 0.0f, 0.0f));
            }        	
            // -------------------------- TEST --------------------------------

            s_LastTick = s_CurrentTick;
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