#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <vector>
#include <map>

#include "includes\glew.h"

#include "Utilities.h"

namespace ae
{
	class VertexBuffer
	{
	public:

		VertexBuffer();

		VertexBuffer(GLenum _target, GLenum _format, GLenum _usage);

		VertexBuffer(unsigned int _vertex_size, unsigned int _vertex_count, const void* data, GLenum _target = GL_ARRAY_BUFFER, GLenum _format = GL_FLOAT, GLenum _usage = GL_STATIC_DRAW);

		VertexBuffer(const std::map<int, int>& _topology, unsigned int _vertex_size, unsigned int _vertex_count, const void* data, GLenum _target = GL_ARRAY_BUFFER, GLenum _format = GL_FLOAT, GLenum _usage = GL_STATIC_DRAW);

		VertexBuffer(unsigned int attribute, unsigned int attribute_size, unsigned int _vertex_size, unsigned int _vertex_count, const void* data, GLenum _target = GL_ARRAY_BUFFER, GLenum _format = GL_FLOAT, GLenum _usage = GL_STATIC_DRAW);

		void init(GLenum _target = GL_ARRAY_BUFFER, GLenum _format = GL_FLOAT, GLenum _usage = GL_STATIC_DRAW);

		void bind() const;

		void unbind() const;

		void setData(unsigned int  _vertex_size, unsigned int _vertex_count, const void* data);

		void setData(unsigned int length, const void* data);

		void setSubData(unsigned int pointer, unsigned int length, const void* data);

		void getSubData(unsigned int pointer, unsigned int length, void* data);

		const std::map<int, int>& getTopology() const
		{
			return topology;
		}

		const unsigned int getID() const { return id; }

		const unsigned int getVertexCount() const { return vertex_count; }

		const unsigned int getVertexSize() const { return vertex_size; }

		const GLenum getTarget() const { return target; }

		const GLenum getFormat() const { return format; }

		const GLenum getUsage() const { return usage; }

		~VertexBuffer();

	protected:

		unsigned int id;

		GLenum target;

		GLenum format;

		GLenum usage;

		std::map<int, int> topology;

		unsigned int vertex_size;

		unsigned int vertex_count;

	private:
	};

	class VertexArray
	{
	public:

		VertexArray();

		void init();

		void bindAttribute(unsigned int attribute, VertexBuffer* buffer, GLenum type, unsigned int count, unsigned int stride, intptr_t offset);

		void setIndexBuffer(VertexBuffer* indexBuffer);

		void bind() const;

		void unbind() const;

		unsigned int getID() const { return id; }

		~VertexArray();

	private:

		unsigned int id;

	};

	class DynamicBuffer
	{
	public:

		DynamicBuffer();

		DynamicBuffer(bool initialize);

		void init();

		void add(VertexBuffer* buffer);

		void setDivisors(const std::map<int, int>& topology);

		void bind() const;

		void unbind() const;

		VertexBuffer* getBuffer(unsigned int index);

		~DynamicBuffer();

	private:

		void update(VertexBuffer* buffer);

		bool topologyCollision(const std::map<int, int>& topology);

		bool initialized;

		VertexArray va;

		std::vector<VertexBuffer*> buffers;

		VertexBuffer* index;

		std::map<int, bool> attr;

	};

	class BufferObject : public MakeSmartExt<BufferObject>
	{
	public:

		BufferObject();

		BufferObject(const std::map<int, int>& topology, GLenum _target = GL_ARRAY_BUFFER, GLenum _format = GL_FLOAT, GLenum _usage = GL_STATIC_DRAW);

		void setData(unsigned int _vertex_size, unsigned int _vertex_count, const void* data);

		void setData(unsigned int length, const void* data);

		void setSubData(unsigned int pointer, unsigned int length, const void* data);

		void bind() const;

		void unbind() const;

		void setVertexCount(unsigned int _vertex_count)
		{
			vertex_count = _vertex_count;
		}

		const unsigned int getVertexCount() const { return vertex_count; }

	private:

		sptr<VertexArray> va;

		sptr<VertexBuffer> buffer;

		GLenum target;
		
		GLenum format;

		GLenum usage;

		unsigned int vertex_size;

		unsigned int vertex_count;

	};

	class FrameBuffer
	{
	public:

		FrameBuffer();

		bool create(int _width, int _height);

		void bind();

		void unbind();

		unsigned int getID() const { return id; }

		unsigned int getTextureID() const { return texture_id; }

	private:

		unsigned int id;

		unsigned int texture_id;

		unsigned int depth_buffer_id;

		int width;

		int height;

	};
};
