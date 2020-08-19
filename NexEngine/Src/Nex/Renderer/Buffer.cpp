#include"nexpch.h"

#include"Buffer.h"
#include"Platform/OpenGL/OpenGLBuffer.h"

namespace Nex {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		return new OpenGLVertexBuffer(vertices, size);
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		return new OpenGLIndexBuffer(indices, count);
	}



	BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements)
		:m_Elements(elements) {
		CalculateOffsetAndStride();
	}
	void BufferLayout::CalculateOffsetAndStride()
	{
		uint32_t offset = 0;
		m_stride = 0;
		for (auto& element : m_Elements) {
			element.offset = offset;
			offset += element.size;
			m_stride += element.size;
		}
	}
}