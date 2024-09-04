#include "Material.h"

namespace vstmr {

	Material::Material()
	{
		shaders.SetVertexShaderPath("../../../../vstmr/assets/shaders/main_vertex_shader.glsl");
		shaders.SetFragmentShaderPath("../../../../vstmr/assets/shaders/main_fragment_shader.glsl");
		shaders.RecompileShader();
	}
}