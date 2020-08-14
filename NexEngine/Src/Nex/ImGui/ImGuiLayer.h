#ifndef IMGUILAYER_H_
#define IMGUILAYER_H_

#include"Nex/Layer.h"
#include"Nex/Core.h"

namespace Nex{
	class NEX_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		float m_Time = 0.0f;
	};
}
#endif // !IMGUILAYER_H_
