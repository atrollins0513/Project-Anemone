#include "..\Anemone\Texture.h"

namespace ae
{
	/* Texture */

	Texture::Texture(unsigned char* data, int length, bool mipmaps, bool flip, GLint mag_filter, GLint min_filter) : Texture()
	{
		load(data, length, mipmaps, flip, mag_filter, min_filter);
	}

	Texture::Texture(const std::string& file_name, bool mipmaps, bool flip, GLint mag_filter, GLint min_filter) : Texture()
	{
		load(file_name, mipmaps, flip, mag_filter, min_filter);
	}

	void Texture::load(unsigned char* data, int length, bool mipmaps, bool flip, GLint mag_filter, GLint min_filter)
	{
		stbi_set_flip_vertically_on_load(flip);
		int bpp;
		stbi_loadf_from_memory(data, length, &texture_width, &texture_height, &bpp, 0);
		create(data, length, bpp, mipmaps, mag_filter, min_filter);
	}

	void Texture::load(const std::string& file_name, bool mipmaps, bool flip, GLint mag_filter, GLint min_filter)
	{
		stbi_set_flip_vertically_on_load(flip);
		int bpp;
		unsigned char* data = stbi_load(file_name.c_str(), &texture_width, &texture_height, &bpp, 0);
		int length = texture_width * texture_height * bpp;
		bpp *= 8;
		create(data, length, bpp, mipmaps, mag_filter, min_filter);
	}

	void Texture::setParameter(GLenum parameter, GLint param_value)
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, parameter, param_value);
		unbind();
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, handle->get());
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::create(unsigned char* data, int length, int bpp, bool mipmaps, GLint mag_filter, GLint min_filter)
	{
		if (data != 0)
		{
			int tempWidth = texture_width;
			int tempHeight = texture_height;
			int level = 0;
			int internalformat = (bpp == 32 ? GL_RGBA8 : GL_RGB8);
			int format = (bpp == 32 ? GL_RGBA : GL_RGB);

			// Generate the OpenGL texture id
			handle = BufferHandle::make(BufferType::TEXTURE);

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

	/* Texture Array */

	TextureArray::TextureArray(unsigned int _width, unsigned int _height, unsigned int _depth, unsigned int _bpp)
	{
		init(_width, _height, _depth, _bpp);
	}

	void TextureArray::init(unsigned int _width, unsigned int _height, unsigned int _depth, unsigned int _bpp)
	{
		width = _width;
		height = _height;
		depth = _depth;
		bpp = _bpp;

		handle = BufferHandle::make(BufferType::TEXTURE);

		internalFormat = (bpp == 32 ? GL_RGBA8 : GL_RGB8);
		format = (bpp == 32 ? GL_RGBA : GL_RGB);

		if (depth > MAX_TEXTURE_DEPTH)
		{
			depth = MAX_TEXTURE_DEPTH;
		}

		bind();

		glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, internalFormat, width, height, depth);

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		unbind();
	}

	int TextureArray::load(unsigned char* data, int length, bool flip)
	{
		stbi_set_flip_vertically_on_load(flip);

		int local_width, local_height, local_bpp;

		stbi_loadf_from_memory(data, length, &local_width, &local_height, &local_bpp, 0);

		if (verifyTexture(local_width, local_height, local_bpp))
		{
			return add(data);
		}
		else
		{
			log("TextureArray", "The texture data does not have the same width, height, or bpp that was defined when the TextureArray was created.");
			return -1;
		}
	}

	int TextureArray::load(const std::string& file_name, bool flip)
	{
		stbi_set_flip_vertically_on_load(flip);

		int local_width, local_height, local_bpp;

		unsigned char* data = stbi_load(file_name.c_str(), &local_width, &local_height, &local_bpp, 0);
		local_bpp *= 8;

		if (verifyTexture(local_width, local_height, local_bpp))
		{
			return add(data);
		}
		else
		{
			log("TextureArray", "Texture " + file_name + " does not have the same width, height, or bpp that was defined when the TextureArray was created.");
			return -1;
		}
	}

	void TextureArray::setParameter(GLenum parameter, GLint param_value)
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D_ARRAY, parameter, param_value);
		unbind();
	}

	void TextureArray::bind() const
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, handle->get());
	}

	void TextureArray::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}

	int TextureArray::add(const unsigned char* data)
	{
		if (current_layer >= depth)
		{
			toss(true, "Failed to add the new texture to the TextureArray because the layer depth has been exceeded. Try increasing the depth specified when the TextureArray was created.");
			return -1;
		}
		else
		{
			bind();
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, current_layer, width, height, 1, format, GL_UNSIGNED_BYTE, data);
			unbind();
			delete data;
			current_layer++;
			return (current_layer - 1);
		}
	}

	bool TextureArray::verifyTexture(unsigned int _width, unsigned int _height, unsigned int _bpp)
	{
		return !(width != _width || height != _height || bpp != _bpp);
	}
};