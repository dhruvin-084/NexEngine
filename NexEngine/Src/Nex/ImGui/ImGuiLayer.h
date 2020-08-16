#ifndef IMGUILAYER_H_
#define IMGUILAYER_H_

#include"Nex/Layer.h"
#include"Nex/Core.h"

#include"Nex/Events/ApplicationEvent.h"
#include"Nex/Events/MouseEvent.h"
#include"Nex/Events/KeyEvent.h"

namespace Nex{
	class NEX_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnImGuiRender() override;

		void Begine();
		void End();




	private:
		float m_Time = 0.0f;
	};
}
#endif // !IMGUILAYER_H_
