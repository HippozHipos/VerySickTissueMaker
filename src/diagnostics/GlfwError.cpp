#include "GlfwError.h"
#include "Logger.h"

namespace vstm {

	void LogGLFWError(int errorCode, const char* desc)
	{
		static int lastError = -1;
		static int count = 0;
		if (lastError == -1)
		{
			lastError = errorCode;
		}
		if (lastError == errorCode)
		{
			if (count < std::numeric_limits<int>::max())
			{
				count++;
			}
		}
		else
		{
			count = 0;
		}
		int maxLogs = 10;
		if (count < maxLogs + 1)
		{
			VSTM_DEBUG_LOGERROR("[GLFW Error]\n[File: {}][Line: {}]\nError code: {}\nError description: {}\n", __FILE__, __LINE__, errorCode, desc);
		}
		else if (count == maxLogs + 1)
		{
			VSTM_DEBUG_LOGINFO("[NOTE] Log omitted because above error occurred more than 10 times\n");
		}
		lastError = errorCode;
	}
}