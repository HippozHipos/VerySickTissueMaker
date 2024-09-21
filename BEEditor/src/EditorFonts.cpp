#include "EditorFonts.h"

namespace bee {

	ImFont* EditorFonts::roboto_regular;
	ImFont* EditorFonts::roboto_bold;

	void EditorFonts::Init()
	{
		ImGuiIO& io = ImGui::GetIO();
		int size = 16;

		std::string roboto = be::ResourcePathHandler::GetFontsPath() + "roboto/";

		std::string robotoRegular = roboto + "/Roboto-Regular.ttf";
		std::string robotoBold = roboto + "/Roboto-Bold.ttf";

		roboto_regular = io.Fonts->AddFontFromFileTTF(robotoRegular.c_str(), size);
		roboto_bold = io.Fonts->AddFontFromFileTTF(robotoBold.c_str(), size);
	}
}
