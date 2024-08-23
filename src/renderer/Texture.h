#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <glad/glad.h>

#include "diagnostics/OpenglError.h"

namespace vstm {

	//Move is not allowed because we store pointer to texture in texture manager. Moving texture would invalidate texture stored in texture manager.
	class Texture
	{
	public:
		Texture();
		Texture(const std::string& path, bool genMipmap = true);
		Texture(unsigned char* data, int width, int height, int channels, bool genMipmap = true);

		//TODO: Write copy constructor and assignment and delete moves
	/*	Texture(Texture&& other) noexcept = delete;
		Texture operator=(Texture&& other) = delete;*/

		~Texture();

	public:
		void Load(const std::string& path, bool genMipmap = true);
		void Load(unsigned char* data, int width, int height, int channels, bool genMipmap = true);

		unsigned char* GetRawData();
		const unsigned char* GetRawData() const;
		int GetWidth() const;
		int GetHeight() const;
		int GetColorChannels() const;
		const std::string& GetPath() const;
		bool Validate() const;
		void GenerateMipMap();
		void Bind();
		Texture HardCopy(const Texture& other) const;

	public:
		template<class... Parameters>
		void SetParameter(Parameters... params)
		{
			glTexParameteri(GL_TEXTURE_2D, params...);
			CheckOpenGLError();
		}

	private:
		std::shared_ptr<unsigned char> m_data = nullptr;
		int m_width = 0;
		int m_height = 0;
		int m_color_channels = 0;
		std::string m_path;

	private:
		GLuint m_texture_id;
	};

	class TextureManager
	{
	public:
		TextureManager();

	public:
		//loads and returns reference
		Texture& LoadRef(const std::string& name, const std::string& path, bool genMipmap = true);
		//gets a texture reference
		Texture& GetRef(const std::string& name);
		//loads and returns pointer
		Texture* Load(const std::string& name, const std::string& path, bool genMipmap = true);
		//get a texture by pointer
		Texture* Get(const std::string& name);

		void Delete(const std::string& name);
		
	private:
		std::unordered_map<std::string, std::shared_ptr<Texture>> m_texture_map;
	};

}