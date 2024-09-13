#pragma once

#ifdef VSTMR_ENTRY_POINT_ALREADY_DEFINED
	#error vstmr EntryPoint.h is only allowed to be included once
#endif

#define VSTMR_ENTRY_POINT_ALREADY_DEFINED


namespace be {
	extern Application* CreateApplication();
}

int main() 
{
	be::Logger::Init();
	be::Application* app = be::CreateApplication();
	app->Run();
	delete app;
}
