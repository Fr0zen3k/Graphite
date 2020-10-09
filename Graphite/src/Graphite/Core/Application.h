//
// Created by Jan Kresic on 9/19/20.
//
#pragma once

#include "grpch.h"

#ifndef GRAPHITE_APPLICATION_H
#define GRAPHITE_APPLICATION_H

#include "Core.h"

#include "grWindow.h"

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
        void run();

        /// <summary>
        /// Event callback function handling all events propagated to the application
        /// </summary>
        /// <param name="event"> Event to be handled </param>
        void OnEvent(grEvent& event);

        /// <summary>
        /// Function to retrieve the window instance of type grWindow
        /// </summary>
        /// <returns> Returns the window reference </returns>
        inline grWindow& GetWindow() { return *m_Window; }

        /// <summary>
        /// Function that retrieves the active application instance
        /// </summary>
        /// <returns> Returns the active application instance </returns>
        inline static Application& Get() { return *s_Instance; }
    private:
        std::unique_ptr<grWindow> m_Window;

        static Application* s_Instance;
    };

    /// <summary>
    /// Extern function defined in the Sandbox, that must return an Application a subclass of it
    /// </summary>
    /// <returns> Must return a pointer to an Application or its subclass </returns>
    Application* CreateApp();
}

#endif //GRAPHITE_APPLICATION_H
