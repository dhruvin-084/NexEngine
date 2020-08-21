#include"nexpch.h"

#include"Nex/Core.h"
#include"Application.h"
#include"Log.h"
#include"Events/ApplicationEvent.h"

#include"Nex/Input.h"
#include"Nex/Keycode.h"

#include"Nex/Renderer/RenderCommand.h"




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
			layout (location = 1) in vec4 aColor;
			
			out vec4 col;
			void main(){
				col = aColor;
				gl_Position = vec4(aPos, 1.0f);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330
			in vec4 col;
			out vec4 FragColor;
			void main(){
				FragColor = col;
			}
		)";

		m_Shader = new Shader(vertexSrc, fragmentSrc);
		float vertices[] = {
			 -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		uint32_t indices[] = {
			0, 1, 2
		};

		m_VertexArray = VertexArray::Create();
		m_VertexArray->Bind();

		VertexBuffer* vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		IndexBuffer* indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		
		BufferLayout layout = {
			{ ShaderDataType::Float3, "aPos" },
			{ ShaderDataType::Float4, "aColor"}
		};
		vertexBuffer->SetLayout(layout);
		

		m_VertexArray->SetVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);


	}

	Application::~Application()
	{
		m_ImGuiLayer->OnDetach();
		m_ImGuiLayer.reset();
		
		m_Window.reset();
		delete m_Shader;
		delete m_VertexArray;

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

			RenderCommand::SetClearColor(glm::vec4(0.0f, 0.0f, 0.1f, 1.0f));
			RenderCommand::Clear();

			m_Shader->Bind();
			m_VertexArray->Bind();

			RenderCommand::DrawIndexed(m_VertexArray);
			
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begine();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->OnImGuiRender();
			m_ImGuiLayer->End();
			

		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}
