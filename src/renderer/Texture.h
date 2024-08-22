#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <glad/glad.h>

#include "diagnostics/OpenglError.h"

namespace vstm {

	class Texture
	{
	public:
		Texture();
		Texture(const std::string& path, bool genMipmap = true);
		Texture(unsigned char* data, bool genMipmap = true);

		//delete copies for now. We need to write these later
		Texture(Texture& other) = delete;
		Texture operator=(Texture& other) = delete;

		Texture(Texture&& other) noexcept = delete;
		Texture operator=(Texture&& other) = delete;

		~Texture();

	public:
		void Load(const std::string& path, bool genMipmap = true);
		void Load(unsigned char* data, bool genMipmap = true);

		unsigned char* GetRawData();
		int GetWidth();
		int GetHeight();
		int GetColorChannels();
		const std::string& GetPath();
		bool Validate();
		void GenerateMipMap();
		void Bind();

	public:
		template<class... Parameters>
		void SetParameter(Parameters... params)
		{
			glTexParameteri(GL_TEXTURE_2D, params...);
			CheckOpenGLError();
		}

	private:
		unsigned char* m_data = nullptr;
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