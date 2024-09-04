#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Texture.h"
#include "diagnostics/Logger.h"
#include "diagnostics/OpenglError.h"

namespace {

	struct textureMemoryDeleter
	{
		void operator()(unsigned char* ptr) { free(ptr); }
	};

}

namespace vstmr {

	Texture::Texture() :
		m_path{ "Texture not loaded from path AND isn't a valid opengl texture" }
	{
	}

	Texture::Texture(const std::string& path, bool genMipmap)
	{
		Load(path, genMipmap);
	}

	Texture::Texture(unsigned char* data, int width, int height, int channels, bool genMipmap)
	{
		Load(data, width, height, channels, genMipmap);
	}

	Texture::Texture(const Texture& other)
	{
		MemberWiseCopyToThis(other);
	}

	Texture& Texture::operator=(const Texture& other)
	{
		if (this != &other)
		{
			MemberWiseCopyToThis(other);
		}
		return *this;
	}

	void Texture::Load(const std::string& path, bool genMipmap)
	{
		m_path = path;
		m_data = std::shared_ptr<unsigned char>(stbi_load(path.c_str(), &m_width, &m_height, &m_color_channels, 0), textureMemoryDeleter());
		glGenTextures(1, &m_texture_id);
		glBindTexture(GL_TEXTURE_2D, m_texture_id);
		GLenum format = (m_color_channels == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data.get());
		if (genMipmap)
		{
			GenerateMipMap();
		}
		CheckOpenGLError();
	}

	void Texture::Load(unsigned char* data, int width, int height, int channels, bool genMipmap)
	{
		m_data = std::shared_ptr<unsigned char>(data, textureMemoryDeleter());;
		m_width = width; m_height = height; m_color_channels = channels;
		m_path = "Texture not loaded from path";
		glGenTextures(1, &m_texture_id);
		glBindTexture(GL_TEXTURE_2D, m_texture_id);
		GLenum format = (m_color_channels == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data.get());
		if (genMipmap)
		{
			GenerateMipMap();
		}
		CheckOpenGLError();
	}

	unsigned char* Texture::GetRawData()
	{
		return m_data.get();
	}

	const unsigned char* Texture::GetRawData() const
	{
		return m_data.get();
	}

	int Texture::GetWidth() const
	{
		return m_width;
	}

	int Texture::GetHeight() const
	{
		return m_height;
	}

	int Texture::GetColorChannels() const
	{
		return m_color_channels;
	}

	const std::string& Texture::GetPath() const
	{
		return m_path;
	}

	bool Texture::Validate() const
	{
		return m_data != nullptr && m_width > 0 && m_height > 0;
	}

	void Texture::GenerateMipMap()
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		CheckOpenGLError();
	}

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_texture_id);
		CheckOpenGLError();
	}

	void Texture::AttachToFrameBuffer()
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture_id, 0);
		CheckOpenGLError();
	}

	void Texture::MemberWiseCopyToThis(const Texture& other)
	{
		m_data = other.m_data;
		m_width = other.m_width;
		m_height = other.m_height;
		m_color_channels = other.m_color_channels;
		m_path = other.m_path;
		m_texture_id = other.m_texture_id;
	}

	void TextureManager::Init()
	{
		stbi_set_flip_vertically_on_load(true);
		unsigned char* defaultColor = (unsigned char*)malloc(sizeof(unsigned char) * 4);
		if (defaultColor)
		{
			defaultColor[0] = 255; defaultColor[1] = 0;
			defaultColor[2] = 255; defaultColor[3] = 255;
			Texture* defaulttex = new Texture{ defaultColor, 1, 1, 4, false };
			m_texture_map.insert(
				std::pair<std::string, std::shared_ptr<Texture>>("default", defaulttex));
		}
		else
		{
			VSTM_CD_LOGERROR("Failed to allocate memory for default texture");
		}
	}

	Texture TextureManager::Load(const std::string& name, const std::string& path, bool genMipmap)
	{
		auto it = m_texture_map.find(name);
		if (it != m_texture_map.end())
		{
			VSTM_CD_LOGINFO("Texture \"{}\" already exists. Attempting to update texture", name);
		}
		else
		{
			VSTM_CD_LOGINFO("Texture \"{}\" not found. Attempting to create new texture", name);
		}
		m_texture_map[name] = std::make_shared<Texture>(path, genMipmap);
		if (m_texture_map[name]->GetRawData() == nullptr)
		{
			VSTM_CD_LOGERROR("Failed to create texture \"{}\"", name);
		}
		else
		{
			VSTM_CD_LOGERROR("Texture \"{}\" created", name);
		}

		return *m_texture_map[name].get();
	}

	Texture TextureManager::Get(const std::string& name)
	{
		auto it = m_texture_map.find(name);
		if (it != m_texture_map.end())
		{
			return *it->second.get();
		}
		else
		{
			VSTM_CD_LOGINFO("Attempting to retrieve texture \"{}\" which doesnt exist. Default texture returned", name);
			return  *m_texture_map["default"].get();
		}
	}

	void TextureManager::Delete(const std::string& name)
	{
		m_texture_map.erase(name);
	}

	Texture TextureManager::HardCopy(const std::string& name, const Texture& other) 
	{
		Texture texture;
		if (other.Validate())
		{
			texture.m_path = other.GetPath();
			texture.m_width = other.GetWidth(); texture.m_height = other.GetHeight(); texture.m_color_channels = other.GetColorChannels();
			size_t dataSize = texture.m_width * texture.m_height * texture.m_color_channels * sizeof(unsigned char);
			texture.m_data = std::shared_ptr<unsigned char>((unsigned char*)malloc(dataSize), textureMemoryDeleter());
			if (texture.m_data)
			{
				memcpy(texture.m_data.get(), other.m_data.get(), dataSize);
				glGenTextures(1, &texture.m_texture_id);
				glBindTexture(GL_TEXTURE_2D, texture.m_texture_id);
				GLenum format = (texture.m_color_channels == 4) ? GL_RGBA : GL_RGB;
				glTexImage2D(GL_TEXTURE_2D, 0, format, texture.m_width, texture.m_height, 0, format, GL_UNSIGNED_BYTE, texture.m_data.get());
				texture.GenerateMipMap();
				CheckOpenGLError();
				if (m_texture_map.insert(
					std::pair<std::string, std::shared_ptr<Texture>>(name,
						std::shared_ptr<Texture>(new Texture{ texture })
						)).second)
				{
					VSTM_CD_LOGINFO("Given texture hardcopied as \"{}\"", name);
					return *m_texture_map[name].get();
				}
				VSTM_CD_LOGINFO("Failed to hardcopy gived texture as \"{}\". Default texture returned", name);
				return *m_texture_map["default"].get();
			}
			else
			{
				VSTM_CD_LOGERROR("Failed to allocate memory to hardcopy given texture as \"{}\". Default texture returned", name);
				return *m_texture_map["default"].get();
			}
		}

		VSTM_CD_LOGWARN("Attempt to hard copy invalid texture as \"{}\". Default texture returned", name);
		return *m_texture_map["default"].get();
	}

	Texture TextureManager::HardCopy(const std::string& name, const std::string& other)
	{
		Texture* t = m_texture_map[name].get();
		return HardCopy("name", *t);
	}
}