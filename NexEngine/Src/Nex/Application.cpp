#include"Application.h"
#include"Log.h"
#include"Events/ApplicationEvent.h"

namespace Nex {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		WindowResizeEvent e(1080, 720);
		if (e.IsInCategory(EventCategoryApplication))
			NEX_TRACE(e.ToString());

		while (true);
	}
}
