#ifndef APPLICATION_H_
#define APPLICATION_H_

#include"Core.h"


namespace Nex {

	class NEX_API Application {
	public:
		Application();
		virtual ~Application();

		void run();
	};

	// to be defined by client
	Application* CreateApplication();
}
#endif // APPLICATION_H_

