#define STB_IMAGE_IMPLEMENTATION
#ifdef STBI_NO_JPEG
	#undef STBI_NO_JPEG
#endif
#include <stb/stb_image.h>

#include "Texture.h"
#include "diagnostics/Logger.h"
#include "diagnostics/OpenglError.h"

#include "iostream"

namespace {

	struct textureMemoryDeleter
	{
		void operator()(unsigned char* ptr) { free(ptr); }
	};

}

namespace be {


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

	Texture Texture::operator=(const Texture& other)
	{
		if (this != &other)
		{
			MemberWiseCopyToThis(other);
		}
		return *this;
	}

	Texture::Texture(Texture&& other) noexcept
	{
		m_data = std::move(other.m_data);
		other.m_data = nullptr;
		m_width = other.m_width;
		m_height = other.m_height;
		m_color_channels = other.m_color_channels;
		m_path = other.m_path;
		m_texture_id = other.m_texture_id;
	}

	Texture& Texture::operator=(Texture&& other) noexcept
	{
		m_data = std::move(other.m_data);
		other.m_data = nullptr;
		m_width = other.m_width;
		m_height = other.m_height;
		m_color_channels = other.m_color_channels;
		m_path = other.m_path;
		m_texture_id = other.m_texture_id;
		return *this;
	}

	//REMINDER: FIXME - Should seperate out opengl functionality from loading functionality
	void Texture::Load(const std::string& path, bool genMipmap)
	{
		m_path = path;
		m_data = std::shared_ptr<unsigned char>(stbi_load(path.c_str(), &m_width, &m_height, &m_color_channels, 0), textureMemoryDeleter());
		if (m_data)
		{
			glGenTextures(1, &m_texture_id);
			glBindTexture(GL_TEXTURE_2D, m_texture_id);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);///////HERE AND IN THE LOAD FUNCTION BELLOW - FIXME///////
			unsigned int format = GetFormatFromChannels(m_color_channels);
			glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data.get());
			if (genMipmap)
			{
				GenerateMipMap();
			}
		}
		else
		{
			Log(Logger::ERR, Logger::CON | Logger::DEB, "{}", stbi_failure_reason());
		}
	}

	void Texture::Load(unsigned char* data, int width, int height, int channels, bool genMipmap)
	{
		m_data = std::shared_ptr<unsigned char>(data, textureMemoryDeleter());
		m_width = width; m_height = height; m_color_channels = channels;
		m_path = "Texture not loaded from path";
		glGenTextures(1, &m_texture_id);
		glBindTexture(GL_TEXTURE_2D, m_texture_id);
		unsigned int format = (m_color_channels == 4) ? GL_RGBA : GL_RGB;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data.get());
		if (genMipmap)
		{
			GenerateMipMap();
		}
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

	unsigned int Texture::Id()
	{
		return m_texture_id;
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
			Log(Logger::ERR, Logger::CON | Logger::DEB, "Failed to allocate memory for default texture");
		}
	}

	Texture TextureManager::Load(const std::string& name, const std::string& path, bool genMipmap)
	{
		auto it = m_texture_map.find(name);
		if (it != m_texture_map.end())
		{
			Log(Logger::ERR, Logger::CON | Logger::DEB, "Texture \"{}\" already exists. Returned already existing texture", name);
			return *it->second;
		}
		else
		{
			Log(Logger::ERR, Logger::CON | Logger::DEB, "Texture \"{}\" not found. Attempting to create new texture", name);
		}
		std::shared_ptr<Texture> tex = std::make_shared<Texture>(path, genMipmap);
		if (!tex->GetRawData())
		{
			Log(Logger::ERR, Logger::CON | Logger::DEB, "Failed to create texture \"{}\". Default texture returned", name);
		}
		else
		{
			Log(Logger::ERR, Logger::CON | Logger::DEB, "Texture \"{}\" created", name);
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
			Log(Logger::ERR, Logger::CON | Logger::DEB, "Attempting to retrieve texture \"{}\" which doesnt exist. Default texture returned", name);
			return  *m_texture_map["default"];
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
					Log(Logger::ERR, Logger::CON | Logger::DEB, "Given texture hardcopied as \"{}\"", name);
					return *m_texture_map[name];
				}
				Log(Logger::ERR, Logger::CON | Logger::DEB, "Failed to hardcopy gived texture as \"{}\". Default texture returned", name);
				return *m_texture_map["default"];
			}
			else
			{
				Log(Logger::ERR, Logger::CON | Logger::DEB, "Failed to allocate memory to hardcopy given texture as \"{}\". Default texture returned", name);
				return *m_texture_map["default"];
			}
		}

		Log(Logger::ERR, Logger::CON | Logger::DEB, "Attempt to hard copy invalid texture as \"{}\". Default texture returned", name);
		return *m_texture_map["default"];
	}

	unsigned int Texture::GetFormatFromChannels(int channels)
	{
		switch (channels)
		{
			case 1: return GL_RED;         // Grayscale
			case 2: return GL_RG;          // Grayscale + Alpha
			case 3: return GL_RGB;         // RGB
			case 4: return GL_RGBA;        // RGBA
			default:
				assert(false && "Unsupported number of channels");
				return 0;
		}
	}


	Texture TextureManager::HardCopy(const std::string& name, const std::string& other)
	{
		Texture* t = m_texture_map[name].get();
		return HardCopy("name", *t);
	}
}