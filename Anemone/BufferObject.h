#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <vector>
#include "includes\glew.h"

#include "Anemone.h"
#include "Error.h"

namespace Anemone
{
	class VertexBuffer
	{
	public:

		VertexBuffer();

		VertexBuffer(GLenum _target, GLenum _usage);

		VertexBuffer(GLenum _target, GLenum _usage, std::size_t length, const void* data);

		VertexBuffer(const VertexBuffer& copy);

		~VertexBuffer();

		void Init(GLenum _target, GLenum _usage);

		void bind();

		void unbind();

		void SetData(std::size_t length, const void* data);

		void SetSubData(std::size_t pointer, std::size_t length, const void* data);

		void GetSubData(std::size_t pointer, std::size_t length, void* data);

		AE_UINT GetId() const { return id; }

		AE_UINT size() const { return dataSize; }

	protected:
	private:

		AE_BOOL set;

		AE_UINT target;

		AE_UINT id;

		AE_UINT dataSize;

		AE_UINT usage;

	};


	class VertexArray
	{
	public:

		VertexArray();

		VertexArray(const VertexArray& copy) { id = copy.id; }

		~VertexArray();

		void Generate();

		void BindAttribute(AE_INT attribute, VertexBuffer& VertexBuffer, GLenum type, AE_UINT count, AE_UINT stride, intptr_t offset);

		void setIndexBuffer(VertexBuffer& indexBuffer);

		void bind();

		void unbind();

		AE_UINT GetId() const { return id; }

	protected:
	private:

		AE_BOOL set;

		AE_UINT id;

	};

	class FrameBuffer
	{
	public:

		FrameBuffer();

		AE_BOOL Create(AE_INT _width, AE_INT _height);

		void bind();

		void unbind();

		AE_UINT GetId() const { return id; }

		AE_UINT GetTextureId() const { return texture_id; }

	protected:
	private:

		AE_UINT id;

		AE_UINT texture_id;

		AE_UINT depth_buffer_id;

		AE_INT width;

		AE_INT height;

	};

	struct RenderObject
	{

		VertexArray vao;

		VertexBuffer vbo;

	};
};
