#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <string>

#include <Windows.h>
#include "includes\glew.h"
#include <gl\GL.h>

#include "stb_image.h"
#include "Utilities.h"

namespace ae
{
	const unsigned int MAX_TEXTURE_DEPTH = 256;

	enum TextureFiltering { NEAREST, LINEAR, TRILINEAR};

	class Texture : public MakeSmartExt<Texture>
	{
	public:

		Texture();

		Texture(unsigned char* data, int length, bool mipmaps, bool flip = true, GLint mag_filter = GL_NEAREST, GLint min_filter = GL_NEAREST);

		Texture(const std::string& file_name, bool mipmaps, bool flip = true, GLint mag_filter = GL_NEAREST, GLint min_filter = GL_NEAREST);

		void load(unsigned char* data, int length, bool mipmaps, bool flip = true, GLint mag_filter = GL_NEAREST, GLint min_filter = GL_NEAREST);

		void load(const std::string& file_name, bool mipmaps, bool flip = true, GLint mag_filter = GL_NEAREST, GLint min_filter = GL_NEAREST);

		void setParameter(GLenum parameter, GLint param_value);

		void bind() const;

		void unbind() const;

		unsigned int id() const { return texture_id; }

		int width() const { return texture_width; }

		int height() const { return texture_height; }

		~Texture();

	protected:

		void create(unsigned char* data, int length, int bpp, bool mipmaps, GLint mag_filter, GLint min_filter);

	private:

		int texture_width;

		int texture_height;

		unsigned int texture_id;

	};

	class TextureArray : public MakeSmartExt<TextureArray>
	{
	public:

		TextureArray();

		TextureArray(unsigned int _width, unsigned int _height, unsigned int _depth, unsigned int _bpp);

		void init(unsigned int _width, unsigned int _height, unsigned int _depth, unsigned int _bpp);

		int load(unsigned char* data, int length, bool flip = true);

		int load(const std::string& file_name, bool flip = true);

		void setParameter(GLenum parameter, GLint param_value);

		void bind() const;

		void unbind() const;

		unsigned int id() const { return texture_id; }

		~TextureArray();

	private:

		int add(const unsigned char* data);

		bool verifyTexture(unsigned int _width, unsigned int _height, unsigned int _bpp);

		unsigned int width;

		unsigned int height;

		unsigned int bpp;

		unsigned int depth;

		GLenum internalFormat;

		GLenum format;

		unsigned int texture_id;

		unsigned int current_layer;

	};

	using TextureRef = sptr<Texture>;

	using TextureArrayRef = sptr<TextureArray>;

};