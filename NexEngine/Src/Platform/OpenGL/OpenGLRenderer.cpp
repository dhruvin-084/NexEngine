#include"nexpch.h"

#include<glad/glad.h>
#include"OpenGLRenderer.h"

namespace Nex {


	void OpenGLRenderer::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void OpenGLRenderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRenderer::BeginScene()
	{
	}
	void OpenGLRenderer::EndScene()
	{
	}
	void OpenGLRenderer::Submit(const VertexArray* vertexArray)
	{
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
	}
}