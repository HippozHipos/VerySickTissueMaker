#pragma once

namespace vstmr {

	class Viewport
	{
	public:
		Viewport(int x, int y, int width, int height);

	public:
		void UpdateViewport();

		//NOTE: REMOVE LATER
		float r = 1.0f;
		float g = 0.0f;
		float b = 0.0f;
		float a = 1.0f;

	private:
		int m_x = 0;
		int m_y = 0;
		int m_width = 0;
		int m_height = 0;
	};

}