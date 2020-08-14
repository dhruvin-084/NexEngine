#include<Nex.h>


class Sandbox : public Nex::Application {
public:
	Sandbox() {
		PushLayer(new Nex::ImGuiLayer());
	}
	~Sandbox() {}

};

Nex::Application* Nex::CreateApplication() {
	return new Sandbox();
}
