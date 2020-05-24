#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <vector>
#include <map>
#include "includes\glew.h"

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

		unsigned int GetId() { return id; }

		unsigned int size() { return dataSize; }

		unsigned int getTarget() { return target; };

		unsigned int getUsage() { return usage; };

	protected:

		bool set;

		unsigned int target;

		unsigned int id;

		unsigned int dataSize;

		unsigned int usage;

	private:
	};

	class VertexArray
	{
	public:

		VertexArray();

		VertexArray(const VertexArray& copy) { set = copy.set; id = copy.id; }

		~VertexArray();

		void init();

		void bindAttribute(int attribute, VertexBuffer& VertexBuffer, GLenum type, unsigned int count, unsigned int stride, intptr_t offset);

		void setIndexBuffer(VertexBuffer& indexBuffer);

		void bind();

		void unbind();

		unsigned int GetId() const { return id; }

	protected:
	private:

		bool set;

		unsigned int id;

	};

	class FrameBuffer
	{
	public:

		FrameBuffer();

		bool create(int _width, int _height);

		void bind();

		void unbind();

		unsigned int getId() const { return id; }

		unsigned int getTextureId() const { return texture_id; }

	protected:
	private:

		unsigned int id;

		unsigned int texture_id;

		unsigned int depth_buffer_id;

		int width;

		int height;

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

		void init(unsigned int vertex_buffer_count, GLenum _target, GLenum _usage);

		void setBuffer(GLenum _target, GLenum _usage, std::size_t length, const void* data);

		void setIndexBuffer(GLenum _usage, std::size_t length, const void* data);

		void bindAttribute(int attribute, unsigned int buffer_id, GLenum type, unsigned int count, unsigned int stride, intptr_t offset);

		void bind();

		void unbind();

		const VertexArray& getVertexArray()
		{
			return vao;
		}

		const VertexBuffer& getVertexBuffer(unsigned int buffer_id)
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

	class BufferObject
	{
	public:

		BufferObject();

		BufferObject(std::map<int, int> topology, GLenum _type = GL_FLOAT, GLenum _target = GL_ARRAY_BUFFER, GLenum _usage = GL_STATIC_DRAW);

		void setData(std::size_t length, const void* data);

		void setSubData(std::size_t pointer, std::size_t length, const void* data);

		void bind();

		void unbind();

		void setVertexCount(unsigned long _vertex_count);

		unsigned long getVertexCount() { return vertex_count; }

	private:

		Anemone::VertexArray va;

		Anemone::VertexBuffer buffer;

		GLenum type, target, usage;

		unsigned long vertex_count;

	};
};
