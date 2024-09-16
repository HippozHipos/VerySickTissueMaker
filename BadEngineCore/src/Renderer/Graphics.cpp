#include <glad/glad.h>

#include "Graphics.h "

namespace be {

	void Graphics::DrawIndexedTraingles(int numIndices)
	{
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
	}

	void Graphics::SetPolygonDrawMode(int mode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, mode);
	}

	void Graphics::SetActiveTextureSlot(int slot)
	{
		glActiveTexture(slot);
	}

	void Graphics::ClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Graphics::ClearBuffer(int buffer)
	{
		glClear(buffer);
	}

	void Graphics::UpdateViewport(int x, int y, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

}