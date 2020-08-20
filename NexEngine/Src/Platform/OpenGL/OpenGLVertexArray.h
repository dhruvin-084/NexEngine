#ifndef OPENGLVERTEXARRAY_H_
#define OPENGLVERTEXARRAY_H_

#include"Nex/Renderer/VertexArray.h"

namespace Nex {
	class OpenGLVertexArray : public VertexArray {
	public: 
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetVertexBuffer(VertexBuffer* vertexBuffer) override;
		virtual void SetIndexBuffer(IndexBuffer* indexBuffer) override;

		virtual VertexBuffer* GetVertexBuffer() const override;
		virtual IndexBuffer* GetIndexBuffer() const override;

	private:
		uint32_t m_RenderID;
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;
	};
}
#endif // !OPENGLVERTEXARRAY_H_
