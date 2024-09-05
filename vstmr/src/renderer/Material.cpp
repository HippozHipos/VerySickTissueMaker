#include "Material.h"

namespace vstmr {

	Material::Material()
	{
		shaders.SetVertexShaderPath("../../../../vstmr/assets/shaders/default_vertex_shader.glsl");
		shaders.SetFragmentShaderPath("../../../../vstmr/assets/shaders/default_fragment_shader.glsl");
		shaders.RecompileShader();
	}
}