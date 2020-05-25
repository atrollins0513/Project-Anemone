#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <Windows.h>
#include "includes\glew.h"
#include <gl\GL.h>

#include "stb_image.h"

namespace Anemone
{
	enum TextureFiltering { NEAREST, LINEAR, TRILINEAR};

	class Texture
	{
	public:

		Texture()
		{
			texture_width = 0;
			texture_height = 0;
			texture_id = 0;
		}

		Texture(unsigned char* data, int length, bool mipmaps, GLint mag_filter = GL_NEAREST, GLint min_filter = GL_NEAREST) : Texture()
		{
			LoadFromData(data, length, mipmaps, mag_filter, min_filter);
		}

		Texture(const char* file_name, bool mipmaps, GLint mag_filter = GL_NEAREST, GLint min_filter = GL_NEAREST) : Texture()
		{
			LoadFromFile(file_name, mipmaps, mag_filter, min_filter);
		};

		void bind();

		void unbind();

		unsigned int id() const { return texture_id; }

		void LoadFromData(unsigned char* data, int length, bool mipmaps, GLint mag_filter = GL_NEAREST, GLint min_filter = GL_NEAREST);

		void LoadFromFile(const char* file_name, bool mipmaps, GLint mag_filter = GL_NEAREST, GLint min_filter = GL_NEAREST);

		void SetParameter(GLenum parameter, GLint param_value);

		int width() const { return texture_width; }

		int height() const { return texture_height; }

		~Texture();

	protected:

		void Create(unsigned char* data, int length, int bpp, bool mipmaps, GLint mag_filter, GLint min_filter);

	private:

		int texture_width;

		int texture_height;

		unsigned int texture_id;

	};
};