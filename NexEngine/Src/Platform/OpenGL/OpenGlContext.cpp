#include"nexpch.h"

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"Nex/Log.h"
#include"Nex/Core.h"
#include"OpenGlContext.h"

namespace Nex {
	OpenGlContext::OpenGlContext(GLFWwindow* windowHandle)
		: m_WindowHaldle(windowHandle) {}

	void OpenGlContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHaldle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NEX_CORE_ASSERT(status, "Fail to load glad.");
	}

	void OpenGlContext::SwapBuffer()
	{
		glfwSwapBuffers(m_WindowHaldle);
	}


}