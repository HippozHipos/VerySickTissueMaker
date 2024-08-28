#pragma once

#ifdef VSTMR_ENTRY_POINT_ALREADY_DEFINED
	#error vstmr EntryPoint.h is only allowed to be included once
#endif

#define VSTMR_ENTRY_POINT_ALREADY_DEFINED


namespace vstmr {
	extern Application* CreateApplication();
}

int main()
{
	vstmr::Logger::Init();
	vstmr::Application* app = vstmr::CreateApplication();
	app->Run();
	delete app;
}
