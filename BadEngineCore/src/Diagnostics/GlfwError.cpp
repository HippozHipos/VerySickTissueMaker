#include "GlfwError.h"
#include "Logger.h"

namespace be {

	void LogGLFWErrorCallback(int errorCode, const char* desc)
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
			BELOG_CD_ERR("[glfw error]\nError code: {}\nError description: {}", errorCode, desc);
		}
		else if (count == maxLogs + 1)
		{
			BELOG_CD_ERR("Log omitted because above error occurred more than 10 times");
		}
		lastError = errorCode;
	}
}