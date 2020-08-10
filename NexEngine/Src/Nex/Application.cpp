#include"nexpch.h"

#include"Application.h"
#include"Log.h"
#include"Events/ApplicationEvent.h"

namespace Nex {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
	

		while (m_Running) {
			m_Window->OnUpdate();
		}
	}
}
