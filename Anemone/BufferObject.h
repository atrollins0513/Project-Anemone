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

		void init(GLenum _target, GLenum _usage);

		void bind();

		void unbind();

		void setData(std::size_t length, const void* data);

		void setSubData(std::size_t pointer, std::size_t length, const void* data);

		void getSubData(std::size_t pointer, std::size_t length, void* data);

		AE_UINT GetId() const { return id; }

		AE_UINT size() const { return dataSize; }

		AE_UINT getTarget() const { return target; };

		AE_UINT getUsage() const { return usage; };

	protected:

		AE_BOOL set;

		AE_UINT target;

		AE_UINT id;

		AE_UINT dataSize;

		AE_UINT usage;

	private:
	};

	class VertexArray
	{
	public:

		VertexArray();

		VertexArray(const VertexArray& copy) { set = copy.set; id = copy.id; }

		~VertexArray();

		void init();

		void bindAttribute(AE_INT attribute, VertexBuffer& VertexBuffer, GLenum type, AE_UINT count, AE_UINT stride, intptr_t offset);

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

		AE_BOOL create(AE_INT _width, AE_INT _height);

		void bind();

		void unbind();

		AE_UINT getId() const { return id; }

		AE_UINT getTextureId() const { return texture_id; }

	protected:
	private:

		AE_UINT id;

		AE_UINT texture_id;

		AE_UINT depth_buffer_id;

		AE_INT width;

		AE_INT height;

	};

	class RenderObject
	{
	public:

		RenderObject();

		RenderObject(const RenderObject& copy)
		{
			vao = copy.vao;
			vbo_array = copy.vbo_array;
			ibo = copy.ibo;
		}

		~RenderObject();

		void init(AE_UINT vertex_buffer_count, GLenum _target, GLenum _usage);

		void setBuffer(GLenum _target, GLenum _usage, std::size_t length, const void* data);

		void setIndexBuffer(GLenum _usage, std::size_t length, const void* data);

		void bindAttribute(AE_INT attribute, AE_UINT buffer_id, GLenum type, AE_UINT count, AE_UINT stride, intptr_t offset);

		void bind();

		void unbind();

		const VertexArray& getVertexArray()
		{
			return vao;
		}

		const VertexBuffer& getVertexBuffer(AE_UINT buffer_id)
		{
			return vbo_array.at(0);
		}

		const VertexBuffer& getIndexBuffer()
		{
			return ibo;
		}
	protected:
	private:
		VertexArray vao;
		std::vector<VertexBuffer> vbo_array;
		VertexBuffer ibo;
	};
};
