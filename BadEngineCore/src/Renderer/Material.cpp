#include "Material.h"
#include "ResourceLoader/ResourcePathHandler.h"

namespace be {

	Material::Material()
	{
		std::string vertexShaderPath = ResourcePathHandler::GetShadersPath() + "default_vertex_shader.glsl";
		std::string fragShaderPath = ResourcePathHandler::GetShadersPath() + "default_fragment_shader.glsl";
		shaders.SetVertexShaderPath(vertexShaderPath.c_str());
		shaders.SetFragmentShaderPath(fragShaderPath.c_str());
		shaders.RecompileShader();
	}
}