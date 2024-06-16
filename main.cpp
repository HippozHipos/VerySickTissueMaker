#include "util/Logger.h"
#include "util/GlfwError.h"

#include "TissueMaker.h"


int main(int argc, char* argv[])
{
	vstm::Logger::Init();
	VSTM_TRACE_LOGINFO("----------------------- START --------------------------\n");
	VSTM_DEBUG_LOGINFO("----------------------- START --------------------------\n");
	glfwSetErrorCallback(vstm::LogGLFWError);
	vstm::TissueMaker tm;
	tm.Run();
	VSTM_TRACE_LOGINFO("----------------------- END ----------------------------\n");
	VSTM_DEBUG_LOGINFO("----------------------- END ----------------------------\n");
}