#include "TextureManager.h"
#include "stb/stb_image.h"

namespace be {

	std::unordered_map<std::string, std::shared_ptr<Texture>> TextureManager::m_texture_map;

	void TextureManager::Init()
	{
		stbi_set_flip_vertically_on_load(true);
		unsigned char* defaultColor = (unsigned char*)malloc(sizeof(unsigned char) * 4);
		if (defaultColor)
		{
			defaultColor[0] = 255; defaultColor[1] = 255;
			defaultColor[2] = 255; defaultColor[3] = 255;
			Texture* defaulttex = new Texture{ defaultColor, 1, 1, 4, false };
			m_texture_map.insert(
				std::pair<std::string, std::shared_ptr<Texture>>("default", defaulttex));
		}
		else
		{
			BELOG_CD_ERR("Failed to allocate memory for default texture");
		}
	}

	Texture TextureManager::Load(const std::string& name, const std::string& path, bool genMipmap)
	{
		auto it = m_texture_map.find(name);
		if (it != m_texture_map.end())
		{
			BELOG_TRC_INFO("Texture \"{}\" already exists. Returned already existing texture", name);
			return *it->second;
		}
		else
		{
			BELOG_TRC_INFO("Texture \"{}\" not found. Attempting to create new texture", name);
		}
		std::shared_ptr<Texture> tex = std::make_shared<Texture>(path, genMipmap);
		if (!tex->GetRawData())
		{
			BELOG_CD_ERR("Failed to create texture \"{}\". Default texture returned", name);
		}
		else
		{
			BELOG_TRC_INFO("Texture \"{}\" created", name);
			m_texture_map[name] = tex;
			return *tex;
		}

		return *m_texture_map["default"];
	}

	Texture TextureManager::Get(const std::string& name)
	{
		auto it = m_texture_map.find(name);
		if (it != m_texture_map.end())
		{
			return *it->second;
		}
		else
		{
			BELOG_CD_WARN("Attempting to retrieve texture \"{}\" which doesnt exist. Default texture returned", name);
			return  *m_texture_map["default"];
		}
	}

	void TextureManager::Delete(const std::string& name)
	{
		m_texture_map.erase(name);
	}

	//Texture TextureManager::HardCopy(const std::string& name, const Texture& other) 
	//{
	//	Texture texture;
	//	if (other.Validate())
	//	{
	//		texture.m_path = other.GetPath();
	//		texture.m_width = other.GetWidth(); texture.m_height = other.GetHeight(); texture.m_color_channels = other.GetColorChannels();
	//		size_t dataSize = texture.m_width * texture.m_height * texture.m_color_channels * sizeof(unsigned char);
	//		texture.m_data = std::shared_ptr<unsigned char>((unsigned char*)malloc(dataSize), textureMemoryDeleter());
	//		if (texture.m_data)
	//		{
	//			memcpy(texture.m_data.get(), other.m_data.get(), dataSize);
	//			glGenTextures(1, &texture.m_texture_id);
	//			glBindTexture(GL_TEXTURE_2D, texture.m_texture_id);
	//			GLenum format = (texture.m_color_channels == 4) ? GL_RGBA : GL_RGB;
	//			glTexImage2D(GL_TEXTURE_2D, 0, format, texture.m_width, texture.m_height, 0, format, GL_UNSIGNED_BYTE, texture.m_data.get());
	//			texture.GenerateMipMap();
	//			CheckOpenGLError();
	//			if (m_texture_map.insert(
	//				std::pair<std::string, std::shared_ptr<Texture>>(name,
	//					std::shared_ptr<Texture>(new Texture{ texture })
	//					)).second)
	//			{
	//				BELOG_TRC_INFO("Given texture hardcopied as \"{}\"", name);
	//				return *m_texture_map[name];
	//			}
	//			BELOG_CD_ERR("Failed to hardcopy gived texture as \"{}\". Default texture returned", name);
	//			return *m_texture_map["default"];
	//		}
	//		else
	//		{
	//			BELOG_CD_ERR("Failed to allocate memory to hardcopy given texture as \"{}\". Default texture returned", name);
	//			return *m_texture_map["default"];
	//		}
	//	}
	//
	//	BELOG_CD_WARN("Attempt to hard copy invalid texture as \"{}\". Default texture returned", name);
	//	return *m_texture_map["default"];
	//}


}