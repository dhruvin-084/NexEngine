#ifndef APPLICATION_H_
#define APPLICATION_H_

#include"nexpch.h"

#include"Core.h"
#include"Events/Event.h"
#include"Window.h"

#include"Nex/Events/ApplicationEvent.h"
#include"Nex/Events/KeyEvent.h"
#include"Nex/Events/MouseEvent.h"
#include"Nex/LayerStack.h"
#include"Nex/ImGui/ImGuiLayer.h"

#include"Nex/Renderer/Shader.h"
#include"Nex/Renderer/Buffer.h"

namespace Nex {

	class NEX_API Application {
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_App; }
		inline Window& GetWindow() { return *m_Window; }

		void run();

	private:

		unsigned int m_VBO, m_VAO, m_EBO;
		Shader* m_Shader;
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;
		bool OnWindowClose(WindowCloseEvent& e);

		static Application* s_App;
		LayerStack m_LayerStack;
		std::unique_ptr<ImGuiLayer> m_ImGuiLayer;
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// to be defined by client
	Application* CreateApplication();
}
#endif // APPLICATION_H_

