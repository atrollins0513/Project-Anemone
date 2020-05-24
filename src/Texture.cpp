#include "..\Anemone\Texture.h"

namespace Anemone
{
	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, texture_id);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::LoadFromData(unsigned char* data, int length, bool mipmaps, GLint mag_filter, GLint min_filter)
	{
		int bpp;
		stbi_loadf_from_memory(data, length, &texture_width, &texture_height, &bpp, 0);
		Create(data, length, bpp, mipmaps, mag_filter, min_filter);
	}

	void Texture::LoadFromFile(const char* file_name, bool mipmaps, GLint mag_filter, GLint min_filter)
	{
		int bpp;
		unsigned char* data = stbi_load(file_name, &texture_width, &texture_height, &bpp, 0);
		int length = texture_width * texture_height * bpp;
		bpp *= 8;
		Create(data, length, bpp, mipmaps, mag_filter, min_filter);
	}

	void Texture::SetParameter(GLenum parameter, GLint param_value)
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, parameter, param_value);
		unbind();
	}

	void Texture::Create(unsigned char* data, int length, int bpp, bool mipmaps, GLint mag_filter, GLint min_filter)
	{
		if (data != 0)
		{
			int tempWidth = texture_width;
			int tempHeight = texture_height;
			int level = 0;
			int internalformat = (bpp == 32 ? GL_RGBA8 : GL_RGB8);
			int format = (bpp == 32 ? GL_RGBA : GL_RGB);

			// Generate the OpenGL texture id
			glGenTextures(1, &texture_id);

			bind();

			glTexImage2D(GL_TEXTURE_2D, 0, internalformat, texture_width, texture_height, 0, format, GL_UNSIGNED_BYTE, data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);

			if (mipmaps)
			{
				glGenerateMipmap(GL_TEXTURE_2D);
			}

			unbind();

			delete data;
		}
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &texture_id);
	}
};