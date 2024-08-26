#pragma once

#ifdef VSTMR_ENTRY_POINT_ALREADY_DEFINED
	#error vstmr EntryPoint.h is only allowed to be included once
#endif

#define VSTMR_ENTRY_POINT_ALREADY_DEFINED

extern vstmr::Application* CreateApplication();

int main()
{
	vstmr::Application* app = CreateApplication();
	app->Run();
	delete app;
}