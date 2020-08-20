#ifndef VERTEXARRAY_H_
#define VERTEXARRAY_H_

#include"Nex/Renderer/Buffer.h"

namespace Nex {
	class VertexArray {
	public:

		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetVertexBuffer(VertexBuffer* vertexBuffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* indexBuffer) = 0;

		virtual VertexBuffer* GetVertexBuffer() const = 0;
		virtual IndexBuffer* GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}
#endif // !VERTEXARRAY_H_
