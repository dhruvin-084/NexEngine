#ifndef RENDERCOMMAND_H_
#define RENDERCOMMAND_H_

#include"Renderer.h"
namespace Nex {
	class RenderCommand {
	public:
		inline static void SetClearColor(const glm::vec4& color) { s_Renderer->SetClearColor(color); }
		inline static void Clear() { s_Renderer->Clear(); }

		inline static void DrawIndexed(const VertexArray* vertexArray) { s_Renderer->Submit(vertexArray); }
	
	private:
		static Renderer* s_Renderer;
	};
}
#endif // !RENDERCOMMAND_H_
