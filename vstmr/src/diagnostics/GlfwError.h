#pragma once

#include "pch.h"

//Reminder from docs:
//Note
//The error callback is called by the thread where the error was generated.
//If you are using GLFW from multiple threads, your error callback needs to be written accordingly.
//Because the description string provided to the callback may have been generated specifically for that error,
//it is not guaranteed to be valid after the callback has returned.If you wish to use it after that, 
//you need to make your own copy of it before returning.

namespace be {

	void LogGLFWError(int errorCode, const char* desc);

}

