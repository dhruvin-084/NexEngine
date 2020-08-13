#ifndef LAYERSTACK_H_
#define LAYERSTACK_H_

#include"Nex/Core.h"
#include"Nex/Layer.h"

namespace Nex {

	class NEX_API LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}
#endif // !LAYERSTACK_H_
