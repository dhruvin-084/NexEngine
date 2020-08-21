#include"nexpch.h"

#include"RenderCommand.h"
#include"Platform/OpenGL/OpenGLRenderer.h"

namespace Nex {
	Renderer* RenderCommand::s_Renderer = new OpenGLRenderer();
}