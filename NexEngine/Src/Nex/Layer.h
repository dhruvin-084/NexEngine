#ifndef LAYER_H_
#define LAYER_H_

#include"Nex/Core.h"
#include"Nex/Events/Event.h"

namespace Nex {

	class NEX_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {};
		virtual void OnImGuiRender() {};

		inline const std::string GetName() { return m_DebugName; }

	private:
		std::string m_DebugName;
	};
}
#endif // !LAYER_H_
