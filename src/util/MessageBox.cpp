#include "MessageBox.h"

void vstm::ErrorMessasgeBox(const std::string& title, const std::string& text)
{
	
#ifdef _WIN32
	MessageBox(NULL, text.c_str(), title.c_str(), MB_ICONERROR);
#else // POSIX
	
#endif
	
}
