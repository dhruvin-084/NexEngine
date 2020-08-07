#ifndef ANTRYPOINT_H_
#define ANTRYPOINT_H_

#ifdef NEX_PLATFORM_WINDOWS

extern Nex::Application* Nex::CreateApplication();

int main(int argc, char** argv) {
	printf("Nex engine started \n");
	auto app = Nex::CreateApplication();
	app->run();
	delete app;

	return 0;
}


#endif // NEX_PLATFORM_WINDOWS

#endif // !ANTRYPOINT_H_
