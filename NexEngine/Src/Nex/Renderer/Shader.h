#ifndef SHADER_H_
#define SHADER_H_

namespace Nex {
	enum class ShaderType {
		Vertex,
		Fragment
	};
	class Shader {
	public:
		Shader(std::string& vertexSrc, std::string& fragmentSrc);
		~Shader();

		void Bind();
		void Unbind();


	private:
		unsigned int m_RenderID;
	};
}
#endif // !SHADER_H_
