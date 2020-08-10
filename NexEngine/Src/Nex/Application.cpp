#include"nexpch.h"

#include"Application.h"
#include"Log.h"
#include"Events/ApplicationEvent.h"



namespace Nex {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{
	}
	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		

		NEX_CORE_TRACE("{0}",e.ToString());
	}

	void Application::run()
	{

		while (m_Running) {
			m_Window->OnUpdate();
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}
