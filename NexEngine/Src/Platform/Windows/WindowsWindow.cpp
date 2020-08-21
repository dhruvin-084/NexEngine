#include"nexpch.h"

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"Nex/Log.h"
#include"WindowsWindow.h"

#include"Nex/Events/ApplicationEvent.h"
#include"Nex/Events/KeyEvent.h"
#include"Nex/Events/MouseEvent.h"

#include"Platform/OpenGL/OpenGlContext.h"

namespace Nex {

	static bool s_GLFWInitialized = false;

	static void GLFWerrorCallback(int error_code, const char* description) {
		NEX_CORE_ERROR("GLFW error: CODE {0}; {1}", error_code, description);
	}

	Window* Window::Create(const WindowProp& prop) {
		return new WindowsWindow(prop);
	}

	WindowsWindow::WindowsWindow(const WindowProp& prop) {
		Init(prop);
	}

	WindowsWindow::~WindowsWindow() {
		ShutDown();
	}

	void WindowsWindow::Init(const WindowProp& prop) {
		m_Data.Title = prop.Title;
		m_Data.Width = prop.Width;
		m_Data.Height = prop.Height;

		NEX_CORE_INFO("Creating window {0}, ({1}, {2})", prop.Title, prop.Width, prop.Height);

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			glfwSetErrorCallback(GLFWerrorCallback);
			NEX_CORE_ASSERT(success, "could not intialize GLFW");
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)prop.Width, (int)prop.Height, prop.Title.c_str(), nullptr, nullptr);

		m_Context = new OpenGlContext(m_Window);
		m_Context->Init();
		
		glViewport(0, 0, prop.Width, prop.Height);

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		

		// GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			glViewport(0, 0, width, height);

			WindowResizeEvent e(width, height);
			data.EventCallback(e);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent e;
			data.EventCallback(e);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS:
				{
					KeyPressedEvent e(key, 0);
					data.EventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(key);
					data.EventCallback(e);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent e(key, 1);
					data.EventCallback(e);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e(button);
					data.EventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e(button);
					data.EventCallback(e);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrollEvent e((float)xoffset, (float)yoffset);
			data.EventCallback(e);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent e((float)xpos, (float)ypos);
			data.EventCallback(e);
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int character) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent e(character);
			data.EventCallback(e);
		});
	}

	void WindowsWindow::ShutDown() {
		glfwDestroyWindow(m_Window);
		delete m_Context;
	}

	void WindowsWindow::OnUpdate() {


		glfwPollEvents();
		m_Context->SwapBuffer();
	}

	void WindowsWindow::SetVSync(bool enabled) {
		glfwSwapInterval((int)enabled);
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}
}