#include"nexpch.h"

#include"VertexArray.h"

#include"Platform/OpenGL/OpenGLVertexArray.h"

namespace Nex {
	VertexArray* VertexArray::Create() {
		return new OpenGLVertexArray();
	}
}