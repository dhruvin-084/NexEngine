#include"nexpch.h"

#include"Nex/Core.h"
#include"Application.h"
#include"Log.h"
#include"Events/ApplicationEvent.h"



namespace Nex {

	Application* Application::s_App = nullptr;

	Application::Application()
	{
		NEX_CORE_ASSERT(!s_App, "There should be only one instance of Application");
		s_App = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{
	}
	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::run()
	{

		while (m_Running) {
			m_Window->OnUpdate();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}
