#pragma once

#include "pch.h"
#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#define NOMINMAX
	#include <Windows.h>
#endif

namespace be {

	void ErrorMessasgeBox(const std::string& title, const std::string& text);

}