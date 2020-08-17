#ifndef GRAPHICSCONTEXT_H_
#define GRAPHICSCONTEXT_H_

namespace Nex {
	class GraphicsContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;
	};
}
#endif // !GRAPHICSCONTEXT_H_
