#include"nexpch.h"

#include"Nex/Core.h"
#include"Application.h"
#include"Log.h"
#include"Events/ApplicationEvent.h"

#include"Nex/Input.h"
#include"Nex/Keycode.h"



#include<glad/glad.h>




namespace Nex {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}

		NEX_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

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
		glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		float vertices[] = {
			 -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		uint32_t indices[] = {
			0, 1, 2
		};

		glGenVertexArrays(1, &m_VAO);


		glBindVertexArray(m_VAO);

		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		{
			

			BufferLayout layout = {
				{ ShaderDataType::Float3, "aPos" },
				{ ShaderDataType::Float4, "aColor"}
			};
			m_VertexBuffer->SetLayout(layout);
		}

		const auto& layout = m_VertexBuffer->GetLayout();
		uint32_t index = 0;
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
								  element.GetComponentCount(), 
								  ShaderDataTypeToOpenGLBaseType(element.type),
								  element.normalized ? GL_TRUE : GL_FALSE,
								  layout.GetStride(),
								  (void*)element.offset);
			index++;
		}


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
