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
	enum class BufferType : unsigned int
	{
		VERTEX = 0,
		ARRAY,
		FRAME,
		TEXTURE
	};

	class BufferHandle
	{
	public:
		const unsigned int get() const;
		unsigned int get();
		static ae::sptr<BufferHandle> make(BufferType _type = BufferType::VERTEX);
		~BufferHandle();
	protected:
		unsigned int id = 0;
		BufferType type = BufferType::VERTEX;
	};

	class VertexBuffer
	{
	public:

		VertexBuffer() = default;

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

		const unsigned int id() const { return handle->get(); }

		const unsigned int getVertexCount() const { return vertex_count; }

		const unsigned int getVertexSize() const { return vertex_size; }

		const GLenum getTarget() const { return target; }

		const GLenum getFormat() const { return format; }

		const GLenum getUsage() const { return usage; }

	protected:

		//unsigned int id;

		sptr<BufferHandle> handle		{ nullptr };
		GLenum target					{ GL_ARRAY_BUFFER };
		GLenum format					{ GL_FLOAT };
		GLenum usage					{ GL_STATIC_DRAW };
		unsigned int vertex_size		{ 0 };
		unsigned int vertex_count		{ 0 };
		std::map<int, int> topology;

	private:
	};

	class VertexArray
	{
	public:

		void init();

		void bindAttribute(unsigned int attribute, VertexBuffer* buffer, GLenum type, unsigned int count, unsigned int stride, intptr_t offset);

		void setIndexBuffer(VertexBuffer* indexBuffer);

		void bind() const;

		void unbind() const;

		const unsigned int id() const { return handle->get(); }

	private:

		sptr<BufferHandle> handle;

	};

	class DynamicBuffer
	{
	public:

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

		VertexBuffer* index		{ nullptr };
		bool initialized		{ false };
		VertexArray va;
		std::vector<VertexBuffer*> buffers;
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

		FrameBuffer() = default;

		FrameBuffer(unsigned int _width, unsigned int _height);

		bool create(unsigned int _width, unsigned int _height);

		void bind();

		void unbind();

		const unsigned int id() const { return handle->get(); }

		unsigned int getTextureID() const { return texture_id; }

	private:

		sptr<BufferHandle> handle;
		unsigned int texture_id			{ 0 };
		unsigned int depth_buffer_id	{ 0 };
		unsigned int width				{ 0 };
		unsigned int height				{ 0 };

	};
};
