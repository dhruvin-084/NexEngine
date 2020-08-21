#ifndef RENDERER_H_
#define RENDERER_H_

#include<glm/glm.hpp>
#include"Nex/Renderer/VertexArray.h"

namespace Nex {
	class Renderer {
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void BeginScene() = 0;
		virtual void EndScene() = 0;

		virtual void Submit(const VertexArray* vertexArray) = 0;
	};
}
#endif // !RENDERER_H_
