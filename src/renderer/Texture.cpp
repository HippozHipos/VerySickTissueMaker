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

	Texture::~Texture()
	{
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

	Texture Texture::HardCopy(const Texture& other) const
	{
		Texture texture;
		if (other.Validate())
		{
			texture.m_path = other.GetPath();
			texture.m_width = other.GetWidth(); texture.m_height = other.GetHeight(); texture.m_color_channels = other.GetColorChannels();
			size_t dataSize = texture.m_width * texture.m_height * texture.m_color_channels * sizeof(int);
			texture.m_data = std::shared_ptr<unsigned char>((unsigned char*)malloc(dataSize), textureMemoryDeleter());
			if (m_data)
			{
				memcpy(m_data.get(), other.GetRawData(), dataSize);
				glGenTextures(1, &texture.m_texture_id);
				glBindTexture(GL_TEXTURE_2D, m_texture_id);
				GLenum format = (m_color_channels == 4) ? GL_RGBA : GL_RGB;
				glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data.get());
				texture.GenerateMipMap();
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

		return texture;
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