#include "GlfwError.h"
#include "Logger.h"

namespace be {

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
			Log(Logger::ERR, Logger::CON | Logger::DEB, "[glfw error]\nError code: {}\nError description: {}", errorCode, desc);
		}
		else if (count == maxLogs + 1)
		{
			Log(Logger::INFO, Logger::CON | Logger::DEB, "Log omitted because above error occurred more than 10 times");
		}
		lastError = errorCode;
	}
}