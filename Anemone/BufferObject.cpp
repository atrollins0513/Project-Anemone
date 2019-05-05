#include "BufferObject.h"

namespace Anemone
{
	/* Vertex Buffer Object */

	VertexBuffer::VertexBuffer()
	{
		target = 0;
		usage = 0;
		dataSize = 0;
	}

	VertexBuffer::VertexBuffer(GLenum _target, GLenum _usage)
	{
		init(_target, _usage);
	}

	VertexBuffer::VertexBuffer(const VertexBuffer& copy)
	{
		target = copy.target;
		id = copy.id;
		dataSize = copy.dataSize;
		usage = copy.usage;
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	VertexBuffer::VertexBuffer(GLenum _target, GLenum _usage, std::size_t length, const void* data)
	{
		target = _target;
		usage = _usage;
		dataSize = 0;
		glGenBuffers(1, &id);
		setData(length, data);
	}

	void VertexBuffer::init(GLenum _target, GLenum _usage)
	{
		target = _target;
		usage = _usage;
		dataSize = 0;
		glGenBuffers(1, &id);
	}

	void VertexBuffer::bind()
	{
		glBindBuffer(target, id);
	}

	void VertexBuffer::unbind()
	{
		glBindBuffer(target, 0);
	}

	void VertexBuffer::setData(std::size_t length, const void* data)
	{
		bind();
		glBufferData(target, length, data, usage);
		dataSize = length;
	}

	void VertexBuffer::setSubData(std::size_t pointer, std::size_t length, const void* data)
	{
		bind();
		glBufferSubData(target, pointer, length, data);
	}

	void VertexBuffer::getSubData(std::size_t pointer, std::size_t length, void* data)
	{
		bind();
		glGetBufferSubData(target, pointer, length, data);
	}

	/* Vertex Array Object */
	VertexArray::VertexArray()
	{

	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &id);
	}

	void VertexArray::init()
	{
		glGenVertexArrays(1, &id);
	}

	void VertexArray::bindAttribute(AE_INT attribute, VertexBuffer& VertexBuffer, GLenum type, AE_UINT count, AE_UINT stride, intptr_t offset)
	{
		bind();
		VertexBuffer.bind();
		glEnableVertexAttribArray(attribute);
		glVertexAttribPointer(attribute, count, type, GL_FALSE, stride, (const GLvoid*)offset);
	}

	void VertexArray::setIndexBuffer(VertexBuffer& indexBuffer)
	{
		bind();
		indexBuffer.bind();
	}

	void VertexArray::bind()
	{
		glBindVertexArray(id);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	/* Frame Buffer Object */
	FrameBuffer::FrameBuffer()
	{
		width = 0;
		height = 0;
	}

	AE_BOOL FrameBuffer::create(AE_INT _width, AE_INT _height)
	{
		width = _width;
		height = _height;

		glGenFramebuffers(1, &id);
		glBindFramebuffer(GL_FRAMEBUFFER, id);

		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_id, 0);

		//GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		//glDrawBuffers(1, DrawBuffers);

		glGenRenderbuffers(1, &depth_buffer_id);
		glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer_id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer_id);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			Error::Log("Framebuffer", "Failed to create the frame buffer");
			return false;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		return true;
	}

	void FrameBuffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, id);
	}

	void FrameBuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	/* Render Object */
	RenderObject::RenderObject()
	{

	}

	RenderObject::~RenderObject()
	{

	}

	void RenderObject::init(AE_UINT vertex_buffer_count, GLenum _target, GLenum _usage)
	{
		vao.init();
	}

	void RenderObject::setBuffer(GLenum _target, GLenum _usage, std::size_t length, const void* data)
	{
		VertexBuffer vbo(_target, _usage, length, data);
		vbo_array.push_back(vbo);
	}

	void RenderObject::setIndexBuffer(GLenum _usage, std::size_t length, const void* data)
	{
		bind();
		ibo = VertexBuffer(GL_ELEMENT_ARRAY_BUFFER, _usage, length, data);
		ibo.bind();
	}

	void RenderObject::bindAttribute(AE_INT attribute, AE_UINT buffer_id, GLenum type, AE_UINT count, AE_UINT stride, intptr_t offset)
	{
		bind();
		vbo_array.at(buffer_id).bind();
		glEnableVertexAttribArray(attribute);
		glVertexAttribPointer(attribute, count, type, GL_FALSE, stride, (const GLvoid*)offset);
	}

	void RenderObject::bind()
	{
		vao.bind();
	}

	void RenderObject::unbind()
	{
		vao.unbind();
	}
};