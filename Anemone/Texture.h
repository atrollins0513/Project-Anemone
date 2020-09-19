#pragma once

#include <string>
#include <Windows.h>
#include "includes\gl3w.h"
#include <gl\GL.h>

#include "Error.h"
#include "stb_image.h"
#include "Utilities.h"
#include "BufferObject.h"

namespace ae
{
	const unsigned int MAX_TEXTURE_DEPTH = 256;

	enum TextureFiltering { NEAREST, LINEAR, TRILINEAR};

	class Texture
	{
	public:

		Texture() = default;

		Texture(unsigned char* data, int length, bool mipmaps, bool flip = true, GLint mag_filter = GL_NEAREST, GLint min_filter = GL_NEAREST);

		Texture(const std::string& file_name, bool mipmaps, bool flip = true, GLint mag_filter = GL_NEAREST, GLint min_filter = GL_NEAREST);

		void load(unsigned char* data, int length, bool mipmaps, bool flip = true, GLint mag_filter = GL_NEAREST, GLint min_filter = GL_NEAREST);

		void load(const std::string& file_name, bool mipmaps, bool flip = true, GLint mag_filter = GL_NEAREST, GLint min_filter = GL_NEAREST);

		void setParameter(GLenum parameter, GLint param_value);

		void bind() const;

		void unbind() const;

		const unsigned int id() const { return handle->get(); }

		const int width() const { return texture_width; }

		const int height() const { return texture_height; }

	protected:

		void create(unsigned char* data, int length, int bpp, bool mipmaps, GLint mag_filter, GLint min_filter);

	private:

		int texture_width			{ 0 };
		int texture_height			{ 0 };
		sptr<BufferHandle> handle	{ nullptr };

	};

	class TextureArray
	{
	public:

		TextureArray() = default;

		TextureArray(unsigned int _width, unsigned int _height, unsigned int _depth, unsigned int _bpp);

		void init(unsigned int _width, unsigned int _height, unsigned int _depth, unsigned int _bpp);

		int load(unsigned char* data, int length, bool flip = true);

		int load(const std::string& file_name, bool flip = true);

		void setParameter(GLenum parameter, GLint param_value);

		void bind() const;

		void unbind() const;

		const unsigned int id() const { return handle->get(); }

	private:

		int add(const unsigned char* data);

		bool verifyTexture(unsigned int _width, unsigned int _height, unsigned int _bpp);

		unsigned int width			{ 0 };
		unsigned int height			{ 0 };
		unsigned int depth			{ 0 };
		unsigned int bpp			{ 32 };
		unsigned int current_layer	{ 0 };
		GLenum internalFormat		{ GL_RGBA8 };
		GLenum format				{ GL_RGBA };
		sptr<BufferHandle> handle	{ nullptr };

	};

};