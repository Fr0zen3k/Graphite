//
// Created by Jan Kresic on 9/19/20.
//
#if defined (_MSC_VER)
#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

#include "grpch.h"

#ifndef GRAPHITE_APPLICATION_H
#define GRAPHITE_APPLICATION_H

#include "Core.h"
#include "Window.h"
#include "Graphite/Renderer/RendererCore/Camera.h"
#include "Benchmarking/Benchmarker.h"


namespace Graphite {

    /// <summary>
    /// Class used for defining a client application used in the main function and in the game loop
    /// </summary>
    class GRAPHITE_API Application {
    public:
        /// <summary>
        /// Constructor and destructor, creates a window, sets the Instance of the application to the latest and sets the even callback function of the window to OnEvent() function
        /// </summary>
        Application();
        virtual ~Application();

        /// <summary>
        /// The function called once every game loop
        /// </summary>
        void Run();

        /// <summary>
        /// Event callback function handling all events propagated to the application
        /// </summary>
        /// <param name="event"> Event to be handled </param>
        void OnEvent(Event& event);

        /// <summary>
        /// Function to retrieve the window instance of type Window
        /// </summary>
        /// <returns> Returns the window reference </returns>
        inline Window* GetWindow() { return m_Window; }

        // FOR GAME LOGIC
        virtual void Start() {}
    	virtual void Tick() {}
    	virtual void Shutdown() {}
    	

        Camera* GetActiveCameraInstance();

		inline void SetActiveCamera(Camera* camera)
		{
            m_ActiveCamera = camera;
		}

        /// <summary>
        /// Function that retrieves the active application instance
        /// </summary>
        /// <returns> Returns the active application instance </returns>
        inline static Application* Get() { return s_Instance; }

        static void SetAppDir(const std::string& path);

        inline static std::string GetAppDir() { return s_ApplicationDirectory; }

        static double DeltaTime();

    	// Test
        static Benchmarker* GetBenchmarker() { return s_Benchmarker; }
        static void InitBenchmarking() { s_Benchmarker = new Benchmarker(); }
    	
    private:
        Window* m_Window;

        Camera* m_ActiveCamera;

        static std::string s_ApplicationDirectory;

        static Application* s_Instance;

        static std::chrono::high_resolution_clock::time_point s_LastTick;
        static std::chrono::high_resolution_clock::time_point s_CurrentTick;

    	// Test
        static Benchmarker* s_Benchmarker;
    };

    /// <summary>
    /// Extern function defined in the Sandbox, that must return an Application a subclass of it
    /// </summary>
    /// <returns> Must return a pointer to an Application or its subclass </returns>
    Application* CreateApp();
}

#endif //GRAPHITE_APPLICATION_H

#if defined (_MSC_VER)
#pragma warning(pop)
#endif