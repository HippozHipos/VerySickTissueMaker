#pragma once
#include <glad/glad.h>


#include <string>
#include <unordered_map>
#include <memory>
#include "diagnostics/OpenglError.h"


namespace be {

	class Texture;
	class TextureManager
	{
	public:
		TextureManager() = default;

	public:
		void Init();
		Texture Load(const std::string& name, const std::string& path, bool genMipmap);
		Texture Get(const std::string& name);
		void Delete(const std::string& name);
		Texture HardCopy(const std::string& name, const Texture& other);
		Texture HardCopy(const std::string& name, const std::string& other);

	private:
		std::unordered_map<std::string, std::shared_ptr<Texture>> m_texture_map;
	};

	class Texture
	{
		friend Texture TextureManager::HardCopy(const std::string& name, const Texture& other);
	public:
		Texture();
		Texture(const std::string& path, bool genMipmap = true);
		Texture(unsigned char* data, int width, int height, int channels, bool genMipmap);

		Texture(const Texture& other);
		Texture operator=(const Texture& other);

		Texture(Texture&& other) noexcept;
		Texture& operator=(Texture&& other) noexcept;

		~Texture() = default;

	public:
		void Load(const std::string& path, bool genMipmap = true);
		void Load(unsigned char* data, int width, int height, int channels, bool genMipmap);

		unsigned char* GetRawData();
		const unsigned char* GetRawData() const;
		int GetWidth() const;
		int GetHeight() const;
		int GetColorChannels() const;
		const std::string& GetPath() const;
		bool Validate() const;
		void GenerateMipMap();
		void Bind();
		void AttachToFrameBuffer();
		unsigned int Id();

	public:
		template<class... Parameters>
		void SetParameter(Parameters... params)
		{
			glTexParameteri(GL_TEXTURE_2D, params...);
			CheckOpenGLError();
		}

	private:
		void MemberWiseCopyToThis(const Texture& other);
		unsigned int GetFormatFromChannels(int channels);

	private:
		std::shared_ptr<unsigned char> m_data = nullptr;
		int m_width = 0;
		int m_height = 0;
		int m_color_channels = 0;
		std::string m_path;

	private:
		GLuint m_texture_id{};
	};
}