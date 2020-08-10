#ifndef APPLICATION_H_
#define APPLICATION_H_

#include"nexpch.h"

#include"Core.h"
#include"Events/Event.h"
#include"Window.h"

namespace Nex {

	class NEX_API Application {
	public:
		Application();
		virtual ~Application();

		void run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// to be defined by client
	Application* CreateApplication();
}
#endif // APPLICATION_H_

