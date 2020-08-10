#include"nexpch.h"

#include"Nex/Log.h"
#include"WindowsWindow.h"

namespace Nex {

	static bool s_GLFWInitialized = false;

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
			NEX_CORE_ASSERT(success, "could not intialize GLFW");
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)prop.Width, (int)prop.Height, prop.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowsWindow::ShutDown() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		glfwSwapInterval((int)enabled);
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}
}