#ifndef BUFFER_H_
#define BUFFER_H_

#include"Nex/Log.h"
#include"Nex/Core.h"

namespace Nex {
	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
		case ShaderDataType::Float:     return 4;
		case ShaderDataType::Float2:    return 4*2;
		case ShaderDataType::Float3:    return 4*3;
		case ShaderDataType::Float4:    return 4*4;
		case ShaderDataType::Int:       return 4;
		case ShaderDataType::Int2:      return 4*2;
		case ShaderDataType::Int3:      return 4*3;
		case ShaderDataType::Int4:      return 4*4;
		case ShaderDataType::Mat3:      return 4*3*3;
		case ShaderDataType::Mat4:      return 4*4*4;
		default:
			break;
		}

		NEX_CORE_ASSERT(false, "Unknown ShaderDataType!");

		return 0;
	}

	struct BufferElement {
		std::string name;
		ShaderDataType type;
		uint32_t size;
		uint32_t offset;
		bool normalized;

		//BufferElement() = default;
		BufferElement(ShaderDataType _type, std::string _name, bool _normalized = false)
			: name(_name), type(_type), size(ShaderDataTypeSize(_type)), offset(0), normalized(_normalized) {

		}

		uint32_t GetComponentCount() const {
			switch (type)
			{
			case ShaderDataType::Float:     return 1;
			case ShaderDataType::Float2:    return 2;
			case ShaderDataType::Float3:    return 3;
			case ShaderDataType::Float4:    return 4;
			case ShaderDataType::Int:       return 1;
			case ShaderDataType::Int2:      return 2;
			case ShaderDataType::Int3:      return 3;
			case ShaderDataType::Int4:      return 4;
			case ShaderDataType::Mat3:      return 3*3;
			case ShaderDataType::Mat4:      return 4*4;
			default:
				break;
			}
			NEX_CORE_ASSERT(false, "Unknown ShaderDataType!");

			return 0;
		}

	};

	class BufferLayout {
	public:
		BufferLayout() = default;
		BufferLayout(std::initializer_list<BufferElement> elements);
			

		inline uint32_t GetStride() const { return m_stride; }
		inline const std::vector<BufferElement>& GetElements() { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetAndStride();

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_stride = 0;
	};



	/////////////////////////////////////////////////////////////////////////////
	////////////// VertexBuffer Class ///////////////////////////////////////////
	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual BufferLayout GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	/////////////////////////////////////////////////////////////////////////////
	////////////// IndexBuffer Class ////////////////////////////////////////////
	class IndexBuffer{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}
#endif // !BUFFER_H_
