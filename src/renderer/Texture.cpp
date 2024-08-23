#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Texture.h"
#include "diagnostics/Logger.h"
#include "diagnostics/OpenglError.h"

namespace vstm {
	Texture::Texture() :
		m_path{ "Texture not loaded from path" }
	{
	}

	Texture::Texture(const std::string& path, bool genMipmap)
	{
		Load(path, genMipmap);
	}

	Texture::Texture(unsigned char* data, int width, int height, int channels, bool genMipmap)
	{
		Load(data, width, height, genMipmap);
	}

	Texture::Texture(Texture& other)
	{
		HardCopyToThis(other);
	}

	Texture& Texture::operator=(Texture& other)
	{
		if (this != &other)
		{
			HardCopyToThis(other);
		}
		return *this;
	}


	Texture::~Texture()
	{
		stbi_image_free(m_data);
	}

	void Texture::Load(const std::string& path, bool genMipmap)
	{
		m_path = path;
		m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_color_channels, 0);
		glGenTextures(1, &m_texture_id);
		glBindTexture(GL_TEXTURE_2D, m_texture_id);
		GLenum format = (m_color_channels == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data);
		if (genMipmap)
		{
			GenerateMipMap();
		}
		CheckOpenGLError();
	}

	void Texture::Load(unsigned char* data, int width, int height, int channels, bool genMipmap)
	{
		m_data = data;
		m_width = width; m_height = height; m_color_channels = channels;
		m_path = "Texture not loaded from path";
		glGenTextures(1, &m_texture_id);
		glBindTexture(GL_TEXTURE_2D, m_texture_id);
		GLenum format = (m_color_channels == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data);
		if (genMipmap)
		{
			GenerateMipMap();
		}
		CheckOpenGLError();
	}

	unsigned char* Texture::GetRawData()
	{
		return m_data;
	}

	int Texture::GetWidth()
	{
		return m_width;
	}

	int Texture::GetHeight()
	{
		return m_height;
	}

	int Texture::GetColorChannels()
	{
		return m_color_channels;
	}

	const std::string& Texture::GetPath()
	{
		return m_path;
	}

	bool Texture::Validate()
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

	void Texture::HardCopyToThis(Texture& other)
	{
		if (other.Validate())
		{
			m_path = other.GetPath();
			m_width = other.GetWidth(); m_height = other.GetHeight(); m_color_channels = other.GetColorChannels();
			size_t dataSize = m_width * m_height * m_color_channels * sizeof(int);
			m_data = (unsigned char*)malloc(dataSize);
			if (m_data)
			{
				memcpy(m_data, other.GetRawData(), dataSize);
				glGenTextures(1, &m_texture_id);
				glBindTexture(GL_TEXTURE_2D, m_texture_id);
				GLenum format = (m_color_channels == 4) ? GL_RGBA : GL_RGB;
				glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data);
				GenerateMipMap();
				CheckOpenGLError();
			}
			else
			{
				VSTM_CD_LOGERROR("Failed to allocate memory for texture");
			}
		}
		else
		{
			VSTM_CD_LOGWARN("Attempt to copy construct invalid texture. No-op");
		}
	}

	TextureManager::TextureManager()
	{
		stbi_set_flip_vertically_on_load(true);
	}

	Texture* TextureManager::Load(const std::string& name, const std::string& path, bool genMipmap)
	{
		auto it = m_texture_map.find(name);
		if (it != m_texture_map.end())
		{
			VSTM_CD_LOGINFO("Texture \"{}\" already exists. Attempting to update texture.\n", name);
		}
		else
		{
			VSTM_CD_LOGINFO("Texture \"{}\" not found. Attempting to create new texture.\n", name);
		}
		m_texture_map[name] = std::make_shared<Texture>(path, genMipmap);
		if (m_texture_map[name]->GetRawData() == nullptr)
		{
			VSTM_CD_LOGERROR("Failed to create texture \"{}\"\n", name);
		}
		else
		{
			VSTM_CD_LOGERROR("Texture \"{}\" created\n", name);
		}

		return m_texture_map[name].get();
	}

	Texture* TextureManager::Get(const std::string& name)
	{
		return m_texture_map[name].get();
	}

	Texture& TextureManager::LoadRef(const std::string& name, const std::string& path, bool genMipmap)
	{
		return *Load(name, path, genMipmap);
	}

	Texture& TextureManager::GetRef(const std::string& name)
	{
		return *m_texture_map[name].get();
	}

	void TextureManager::Delete(const std::string& name)
	{
		m_texture_map.erase(name);
	}
}