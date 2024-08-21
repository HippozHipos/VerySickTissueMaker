#include "diagnostics/Logger.h"
#include "diagnostics/GlfwError.h"
#include "Application.h"
#include "glad/glad.h"

int main(int argc, char* argv[])
{
	vstm::Logger::Init();
	VSTM_TRACE_LOGINFO("----------------------- START --------------------------\n");
	VSTM_DEBUG_LOGINFO("----------------------- START --------------------------\n");
	glfwSetErrorCallback(vstm::LogGLFWError);
	vstm::Application tm;
	tm.Run();
	VSTM_TRACE_LOGINFO("----------------------- END ----------------------------\n");
	VSTM_DEBUG_LOGINFO("----------------------- END ----------------------------\n");
}