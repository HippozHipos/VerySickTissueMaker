#pragma once

#ifdef BADENGINE_ENTRY_POINT_ALREADY_DEFINED
	#error EntryPoint.h is only allowed to be included once
#endif

#define BADENGINE_ENTRY_POINT_ALREADY_DEFINED


namespace be {
	extern Application* CreateApplication();
}

int main() 
{
	be::Logger::Init();
	be::ResourcePathHandler::Init();
	be::Application* app = be::CreateApplication();
	app->Run();
	delete app;
}
