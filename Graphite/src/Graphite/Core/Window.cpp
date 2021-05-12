#include "Graphite/Core/grpch.h"

#include "Window.h"


namespace Graphite {
	
	static bool s_GLFWInitialized = false;

	Window * Window::grCreateWindow(const WindowInfo& props)
	{
		return new Window(props);
	}

	Window::Window(const WindowInfo& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.VSync = false;

		Init();
	}

	Window::~Window() {
		Shutdown();
	}

	void Window::Update() {
		glfwPollEvents();
		glfwSwapBuffers(m_WindowInstance);
	}

	void Window::SetVSync(bool status) {
		if(status) {
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_Data.VSync = status;
	}

	void Window::ChangeTitle(const std::string& newTitle)
	{
		m_Data.Title = newTitle;
		glfwSetWindowTitle(m_WindowInstance, newTitle.c_str());
	}


	void Window::Init() {

		GR_CORE_LOG_INFO("Creating a window {0} ({1} x {2})", m_Data.Title, m_Data.Width, m_Data.Height);
		
		if(!s_GLFWInitialized) {
			
			int res = glfwInit();

			GR_CORE_ASSERT(res, "Could not initialize GLFW!");

			glfwSetErrorCallback([](int err, const char * description)
			{
				GR_CORE_LOG_ERROR("GLFW Error: ({0}): {1}", err, description);
			});

			s_GLFWInitialized = true;
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);			//implement later, leave for now

		m_WindowInstance = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
//		glfwMakeContextCurrent(m_WindowInstance);
		glfwSetWindowUserPointer(m_WindowInstance, &m_Data);
//		SetVSync(false);

		//--------------------------------------glfw event callbacks--------------------------------------------

		//Window size change callback
		glfwSetWindowSizeCallback(m_WindowInstance, [](GLFWwindow * window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Height = height;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		//Window close callback
		glfwSetWindowCloseCallback(m_WindowInstance, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		//Key callback
		glfwSetKeyCallback(m_WindowInstance, [](GLFWwindow * window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyDownEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyUpEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyDownEvent event(key, 1);			//implement repeats later
					data.EventCallback(event);
					break;
				}
			}
		});

		//Mouse button callback
		glfwSetMouseButtonCallback(m_WindowInstance, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonDownEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonUpEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		//Mouse scroll callback
		glfwSetScrollCallback(m_WindowInstance, [](GLFWwindow * window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrollEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		//Mouse move callback
		glfwSetCursorPosCallback(m_WindowInstance, [](GLFWwindow * window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovEvent event(xPos, yPos);
			data.EventCallback(event);
		});

		//***********************IMPLEMENT MORE EVENT TYPES LATER*****************************

		//-----------------------------------end of glfw event callbacks--------------------------------------------

	}

	void Window::Shutdown() {
		glfwDestroyWindow(m_WindowInstance);
	}

}