#pragma once

#include <imgui.h>
#include <BECore/BECore.h>

namespace bee {

	class EditorFonts 
	{
	public:
		static void Init();
		static ImFont* roboto_regular;
		static ImFont* roboto_bold;
	};

}