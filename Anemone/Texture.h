#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <Windows.h>
#include "includes\glew.h"
#include <gl\GL.h>

#include "Anemone.h"
#include "stb_image.h"

namespace Anemone
{
	enum TextureFiltering { NEAREST, LINEAR, TRILINEAR};

	class Texture
	{
	public:

		void bind();

		void unbind();

		AE_UINT id() const { return texture_id; }

		void LoadFromData(AE_UCHAR* data, AE_INT length, AE_BOOL mipmaps, GLint mag_filter = GL_NEAREST, GLint min_filter = GL_NEAREST);

		void LoadFromFile(AE_CHAR* file_name, AE_BOOL mipmaps, GLint mag_filter = GL_NEAREST, GLint min_filter = GL_NEAREST);

		void SetParameter(GLenum parameter, GLint param_value);

		AE_INT width() const { return texture_width; }

		AE_INT height() const { return texture_height; }

		~Texture();

	protected:

		void Create(AE_UCHAR* data, AE_INT length, AE_INT bpp, AE_BOOL mipmaps, GLint mag_filter, GLint min_filter);

	private:

		AE_INT texture_width;

		AE_INT texture_height;

		AE_UINT texture_id;

	};
};