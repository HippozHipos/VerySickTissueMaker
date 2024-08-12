#include "util/Logger.h"
#include "util/GlfwError.h"
#include "Application.h"
#include "Renderer/OpenglError.h"
#include "glad/glad.h"
#include "glm/glm.hpp"

int main(int argc, char* argv[])
{
	vstm::Logger::Init();
	VSTM_TRACE_LOGINFO("----------------------- START --------------------------\n");
	VSTM_DEBUG_LOGINFO("----------------------- START --------------------------\n");
	glfwSetErrorCallback(vstm::LogGLFWError);
	vstm::Application tm;
	glDebugMessageCallback(vstm::OpenGLErrorMessageCallback, "OpenGL Error In VSTM");
	tm.Run();
	VSTM_TRACE_LOGINFO("----------------------- END ----------------------------\n");
	VSTM_DEBUG_LOGINFO("----------------------- END ----------------------------\n");
}