#pragma once 

#include "Renderer/Texture.h"

namespace be {

	class TextureManager
	{
	public:
		TextureManager() = default;

	public:
		static void Init();
		static Texture Load(const std::string& name, const std::string& path, bool genMipmap);
		static Texture Get(const std::string& name);
		static void Delete(const std::string& name);

	private:
		static std::unordered_map<std::string, std::shared_ptr<Texture>> m_texture_map;
	};

}