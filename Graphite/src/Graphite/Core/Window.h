#pragma once

#include "grpch.h"

#ifndef GRAPHITE_WINDOW_H
#define GRAPHITE_WINDOW_H

#include "Core.h"
#include "Graphite/EventCore/Events.h"

#include "GLFW/glfw3.h"

namespace Graphite {

	/// <summary>
	/// Struct used for easier window init, holds the needed info to init a non-default window, the values are passed to a WindowData instance within the Window class
	/// </summary>
	struct WindowInfo {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowInfo(const std::string & title = "Graphite Engine", 
					unsigned int width = 1280, 
					unsigned int height = 720)
			: Title(title), Width(width), Height(height) { }
	};

	/// <summary>
	/// Class representing a window for the renderer to use, holds a glfwWindow, as well as the width and height data and the window title, which is changeable
	/// </summary>
	class GRAPHITE_API Window {
		friend class VkGraphicsContext;
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		/// <summary>
		/// Constructor, calls the Init() function
		/// </summary>
		/// <param name="props"> Used for the info needed to create a custom non-default window instance </param>
		Window(const WindowInfo& props);
		/// <summary>
		/// Destructor, calls the Shutdown() function
		/// </summary>
		~Window();

		/// <summary>
		/// Function called once per tick, updated the frame with the newest information regarding rendering, events and such
		/// </summary>
		void Update();

		/// <summary>
		/// Getters for the dimensions of the window
		/// </summary>
		/// <returns> The dimensions of the window each </returns>
		inline uint32_t GetHeight() { return m_Data.Height; }
		inline uint32_t GetWidth() { return m_Data.Width; }

		/// <summary>
		/// Getter for the GLFW window instance, needed for the renderer
		/// </summary>
		/// <returns> Returns the GLFW window used for rendering </returns>
		inline GLFWwindow* GetNativeWindow() { return m_WindowInstance; }

		/// <summary>
		/// Sets the new title, deletes the previous one
		/// </summary>
		/// <param name="newTitle"> The value title is set to </param>
		void ChangeTitle(const std::string& newTitle);

		/// <summary>
		/// Sets the event callback function used to retrieve events from the GLFW window
		/// </summary>
		/// <param name="callback"> The function to be set as the callback </param>
		inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		/// <summary>
		/// Sets VSynch to the given value, if true, VSynch will be active
		/// </summary>
		/// <param name="status"> Determines weather VSynch will be active or not </param>
		void SetVSync(bool status);
		/// <summary>
		/// Getter for the VSynch status
		/// </summary>
		/// <returns> Returns the VSynch status </returns>
		inline bool IsVSyncOn() { return m_Data.VSync; }

		/// <summary>
		/// Static function for creating a Window instance
		/// </summary>
		/// <param name="props"> WindowInfo needed for creating a non-default window </param>
		/// <returns> Returns the pointer to the window instance created, window needs to be deleted before closing the app </returns>
		static Window* grCreateWindow(const WindowInfo& props = WindowInfo());

	private:
		/// <summary>
		/// A function used to initialize the window as well as init GLFW, but not Vulkan
		/// </summary>
		void Init();
		/// <summary>
		/// A function for window and GLFW shutdown, but not Vulkan
		/// </summary>
		void Shutdown();

		/// <summary>
		/// GLFW window instances
		/// </summary>
		GLFWwindow* m_WindowInstance;

		/// <summary>
		/// Struct used to hold the raw info data of the window, as well as VSync status and a general event callback function used for event dispatching
		/// </summary>
		struct WindowData {
			std::string Title;
			uint32_t Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}

#endif //GRAPHITE_WINDOW_H