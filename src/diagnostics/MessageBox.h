#pragma once

#include <string>
#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#define NOMINMAX
	#include <Windows.h>
#endif

namespace vstm {

	void ErrorMessasgeBox(const std::string& title, const std::string& text);

}