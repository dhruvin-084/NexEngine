#ifndef ANTRYPOINT_H_
#define ANTRYPOINT_H_

#ifdef NEX_PLATFORM_WINDOWS



extern Nex::Application* Nex::CreateApplication();

int main(int argc, char** argv) {

	Nex::Log::Init();
	NEX_CORE_WARN("Initialize Nex Engine");
	int a = 5;
	NEX_INFO("Hello! var={0}", a);
	auto app = Nex::CreateApplication();
	app->run();
	delete app;

	return 0;
}


#endif // NEX_PLATFORM_WINDOWS

#endif // !ANTRYPOINT_H_
