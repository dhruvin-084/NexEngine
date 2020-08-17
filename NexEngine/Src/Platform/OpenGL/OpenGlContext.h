#ifndef OPENGLCONTEXT_H_
#define OPENGLCONTEXT_H_

#include"Nex/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Nex {
	class OpenGlContext : public GraphicsContext {
	public:
		OpenGlContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffer() override;
	private:
		GLFWwindow* m_WindowHaldle;
	};
}
#endif // !OPENGLCONTEXT_H_
