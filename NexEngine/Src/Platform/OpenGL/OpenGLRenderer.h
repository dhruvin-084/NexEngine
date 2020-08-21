#ifndef OPENGLREDERER_H_
#define OPENGLREDERER_H_

#include"Nex/Renderer/Renderer.h"

namespace Nex {
	class OpenGLRenderer : public Renderer {
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void BeginScene() override;
		virtual void EndScene() override;

		virtual void Submit(const VertexArray* vertexArray) override;
	};
}
#endif // !OPENGLREDERER_H_
