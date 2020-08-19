#ifndef OPENGLBUFFER_H_
#define OPENGLBUFFER_H_

#include"Nex/Renderer/Buffer.h"
namespace Nex {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		uint32_t m_RenderID;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual inline uint32_t GetCount() const override { return m_Count; }
	private:
		uint32_t m_Count;
		uint32_t m_RenderID;
	};
}
#endif // !OPENGLBUFFER_H_
