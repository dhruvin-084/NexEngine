#include"nexpch.h"

#include<glad/glad.h>

#include"Nex/Log.h"
#include"Nex/Core.h"

#include"OpenGLVertexArray.h"

namespace Nex {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}

		NEX_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}



	OpenGLVertexArray::OpenGLVertexArray() {
		glGenVertexArrays(1, &m_RenderID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RenderID);

		delete m_IndexBuffer;
		delete m_VertexBuffer;
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RenderID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	
	void OpenGLVertexArray::SetVertexBuffer(VertexBuffer* vertexBuffer)
	{
		NEX_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Layout is not set.");
		
		glBindVertexArray(m_RenderID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		uint32_t index = 0;
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(void*)element.offset);
			index++;
		}
		m_VertexBuffer = vertexBuffer;
	}
	
	void OpenGLVertexArray::SetIndexBuffer(IndexBuffer* indexBuffer)
	{
		glBindVertexArray(m_RenderID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
	VertexBuffer* OpenGLVertexArray::GetVertexBuffer() const
	{
		return m_VertexBuffer;
	}
	IndexBuffer* OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}
}