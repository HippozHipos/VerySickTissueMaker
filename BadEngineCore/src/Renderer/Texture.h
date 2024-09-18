#pragma once
#include "pch.h"
#include <glad/glad.h>
#include "Diagnostics/OpenglError.h"


namespace be {

	class Texture
	{
	public:
		Texture();
		Texture(const std::string& path, bool genMipmap = true);
		Texture(unsigned char* data, int width, int height, int channels, bool genMipmap);

		Texture(const Texture& other);
		Texture operator=(const Texture& other);

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