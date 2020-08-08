#include<Nex.h>


class Sandbox : public Nex::Application {
public:
	Sandbox() {}
	~Sandbox() {}

};

Nex::Application* Nex::CreateApplication() {
	return new Sandbox();
}
