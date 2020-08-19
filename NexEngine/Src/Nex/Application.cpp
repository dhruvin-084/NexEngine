#include"nexpch.h"

#include"Nex/Core.h"
#include"Application.h"
#include"Log.h"
#include"Events/ApplicationEvent.h"

#include"Nex/Input.h"
#include"Nex/Keycode.h"



#include<glad/glad.h>




namespace Nex {

	Application* Application::s_App = nullptr;

	Application::Application()
	{
		NEX_CORE_ASSERT(!s_App, "There should be only one instance of Application");
		s_App = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		m_ImGuiLayer = std::unique_ptr<ImGuiLayer>(new ImGuiLayer());
		m_ImGuiLayer->OnAttach();

		std::string vertexSrc = R"(
			#version 330
			layout (location = 0) in vec3 aPos;
			void main(){
				gl_Position = vec4(aPos, 1.0f);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330
			out vec4 FragColor;
			void main(){
				FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
			}
		)";

		m_Shader = new Shader(vertexSrc, fragmentSrc);
		glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		float vertices[] = {
			0.0f, 0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f
		};

		uint32_t indices[] = {
			0, 1, 2
		};

		glGenVertexArrays(1, &m_VAO);


		glBindVertexArray(m_VAO);

		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

	}

	Application::~Application()
	{
		m_ImGuiLayer->OnDetach();
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
			m_Shader->Bind();
			glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
			/*
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begine();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->OnImGuiRender();
			m_ImGuiLayer->End();
			*/

		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}
