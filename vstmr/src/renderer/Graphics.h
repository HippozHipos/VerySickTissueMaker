#pragma once
#include "pch.h"

namespace be {

	class Graphics
	{
	public:
		Graphics() = default;

	public:
		static void DrawIndexedTraingles(int numIndices);
		static void SetPolygonDrawMode(int mode);
		static void SetActiveTextureSlot(int slot);
		static void ClearColor(float r, float g, float b, float a);
		static void ClearBuffer(int buffer);
		static void UpdateViewport(int x, int y, int width, int height);
	};

}