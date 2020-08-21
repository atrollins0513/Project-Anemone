#include "..\Anemone\BufferObject.h"

namespace ae
{
	// Vertex Buffer //

	VertexBuffer::VertexBuffer()
	{
		id = 0;
		target = GL_ARRAY_BUFFER;
		format = GL_FLOAT;
		usage = GL_STATIC_DRAW;
		vertex_size = 0;
		vertex_count = 0;
	}

	VertexBuffer::VertexBuffer(GLenum _target, GLenum _format, GLenum _usage)
	{
		init(_target, _format, _usage);
	}

	VertexBuffer::VertexBuffer(unsigned int _vertex_size, unsigned int _vertex_count, const void* data, GLenum _target, GLenum _format, GLenum _usage)
	{
		init(_target, _format, _usage);
		setData(_vertex_size, _vertex_count, data);
	}

	VertexBuffer::VertexBuffer(const std::map<int, int>& _topology, unsigned int _vertex_size, unsigned int _vertex_count, const void* data, GLenum _target, GLenum _format, GLenum _usage)
	{
		init(_target, _format, _usage);
		topology = _topology;
		setData(_vertex_size, _vertex_count, data);
	}

	VertexBuffer::VertexBuffer(unsigned int attribute, unsigned int attribute_size, unsigned int _vertex_size, unsigned int _vertex_count, const void* data, GLenum _target, GLenum _format, GLenum _usage)
	{
		init(_target, _format, _usage);
		topology.emplace(attribute, attribute_size);
		setData(_vertex_size, _vertex_count, data);
	}

	void VertexBuffer::init(GLenum _target, GLenum _format, GLenum _usage)
	{
		target = _target;
		format = _format;
		usage = _usage;
		glGenBuffers(1, &id);
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(target, id);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(target, 0);
	}

	void VertexBuffer::setData(unsigned int _vertex_size, unsigned int _vertex_count, const void* data)
	{
		vertex_size = _vertex_size;
		vertex_count = _vertex_count;
		bind();
		glBufferData(target, vertex_size * vertex_count, data, usage);
	}

	void VertexBuffer::setData(unsigned int length, const void* data)
	{
		bind();
		glBufferData(target, length, data, usage);
	}

	void VertexBuffer::setSubData(unsigned int pointer, unsigned int length, const void* data)
	{
		bind();
		glBufferSubData(target, pointer, length, data);
	}

	void VertexBuffer::getSubData(unsigned int pointer, unsigned int length, void* data)
	{
		bind();
		glGetBufferSubData(target, pointer, length, data);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	// Vertex Array //

	VertexArray::VertexArray()
	{
		id = 0;
	}

	void VertexArray::init()
	{
		glGenVertexArrays(1, &id);
	}

	void VertexArray::bindAttribute(unsigned int attribute, VertexBuffer* buffer, GLenum type, unsigned int count, unsigned int stride, intptr_t offset)
	{
		bind();
		buffer->bind();
		glEnableVertexAttribArray(attribute);
		glVertexAttribPointer(attribute, count, type, GL_FALSE, stride, (const GLvoid*)offset);
	}

	void VertexArray::setIndexBuffer(VertexBuffer* indexBuffer)
	{
		bind();
		indexBuffer->bind();
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(id);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &id);
	}

	// Dynamic Buffer //

	DynamicBuffer::DynamicBuffer()
	{
		index = nullptr;
		initialized = false;
	}

	DynamicBuffer::DynamicBuffer(bool initialize)
	{
		index = nullptr;
		initialized = false;
		if (initialize)
		{
			init();
		}
	}

	void DynamicBuffer::init()
	{
		if (!initialized)
		{
			initialized = true;
			va.init();
		}
	}

	void DynamicBuffer::add(VertexBuffer* buffer)
	{
		if (buffer->getTarget() == GL_ELEMENT_ARRAY_BUFFER)
		{
			index = buffer;
		}
		else
		{
			if (std::find(buffers.begin(), buffers.end(), buffer) == buffers.end())
			{
				buffers.push_back(buffer);
				update(buffer);
			}
			else
			{
				ae::log("DynamicBuffer", "Buffer has already been added.");
			}
		}
	}

	void DynamicBuffer::setDivisors(const std::map<int, int>& topology)
	{
		va.bind();
		for (auto t : topology)
		{
			glVertexAttribDivisor(t.first, t.second);
		}
		va.unbind();
	}

	void DynamicBuffer::bind() const
	{
		va.bind();
	}

	void DynamicBuffer::unbind() const
	{
		va.unbind();
	}

	VertexBuffer* DynamicBuffer::getBuffer(unsigned int index)
	{
		return buffers.at(index);
	}

	DynamicBuffer::~DynamicBuffer()
	{
		for (auto it = buffers.begin(); it != buffers.end();)
		{
			if ((*it))
			{
				delete (*it);
				it = buffers.erase(it);
			}
			++it;
		}

		if (index)
		{
			delete index;
			index = nullptr;
		}
	}

	void DynamicBuffer::update(VertexBuffer* buffer)
	{
		init();

		int sum = 0;
		int offset = 0;

		if (buffer->getTarget() == GL_ARRAY_BUFFER)
		{
			auto topology = buffer->getTopology();
			if (topology.size() > 0)
			{
				if (!topologyCollision(topology))
				{
					for (auto t : topology)
					{
						attr.emplace(t.first, true);
						sum += t.second;
					}

					for (auto t : topology)
					{
						va.bindAttribute(t.first, buffer, buffer->getFormat(), t.second, buffer->getVertexSize(), offset);
						offset += t.second * (sum == 0 ? 1 : (buffer->getVertexSize() / sum));
					}
				}
				else
				{
					ae::log("DynamicBuffer", "Collision in topology attributes.");
				}
			}
		}
		else if (buffer->getTarget() == GL_ELEMENT_ARRAY_BUFFER)
		{
			va.setIndexBuffer(buffer);
		}
	}

	bool DynamicBuffer::topologyCollision(const std::map<int, int>& topology)
	{
		for (auto t : topology)
		{
			bool collision = (attr.find(t.first) != attr.end());
			if (collision)
			{
				return true;
			}
		}
		return false;
	}

	// Buffer Object //

	BufferObject::BufferObject()
	{
		format = target = usage = 0;
		vertex_count = 0;
		vertex_size = 0;
	}

	BufferObject::BufferObject(const std::map<int, int>& topology, GLenum _target, GLenum _format, GLenum _usage)
	{
		target = _target;
		format = _format;
		usage = _usage;
		vertex_count = 0;
		vertex_size = 0;

		va.init();
		buffer.init(target, format, usage);

		int sum = 0;
		int offset = 0;

		for (auto t : topology)
		{
			sum += t.second;
		}

		for (auto t : topology)
		{
			va.bindAttribute(t.first, &buffer, format, t.second, sum * sizeof(float), offset);
			offset += t.second * sizeof(float);
		}

		buffer.unbind();
		va.unbind();
	}

	void BufferObject::setData(unsigned int _vertex_size, unsigned int _vertex_count, const void* data)
	{
		vertex_size = _vertex_size;
		vertex_count = _vertex_count;
		buffer.setData(vertex_size, vertex_count, data);
	}

	void BufferObject::setData(unsigned int length, const void* data)
	{
		buffer.setData(length, data);
	}

	void BufferObject::setSubData(unsigned int pointer, unsigned int length, const void* data)
	{
		buffer.setSubData(pointer, length, data);
	}

	void BufferObject::bind() const
	{
		va.bind();
	}

	void BufferObject::unbind() const
	{
		va.unbind();
	}

	/*
	// Vertex Buffer Object

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

	// Vertex Array Object

	VertexArray::VertexArray()
	{
		id = 0;
		set = false;
	}

	void VertexArray::init()
	{
		glGenVertexArrays(1, &id);
	}

	void VertexArray::bindAttribute(int attribute, VertexBuffer& VertexBuffer, GLenum type, unsigned int count, unsigned int stride, intptr_t offset)
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

	VertexArray::VertexArray(const VertexArray& copy)
	{
		set = copy.set;
		id = copy.id;
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &id);
	}

	// Render Object

	RenderObject::RenderObject()
	{

	}

	void RenderObject::init(unsigned int vertex_buffer_count, GLenum _target, GLenum _usage)
	{
		vao.init();
	}

	void RenderObject::setBuffer(GLenum _target, GLenum _usage, std::size_t length, const void* data)
	{
		VertexBuffer vbo(_target, _usage, length, data);
		buffers.push_back(vbo);
	}

	void RenderObject::setIndexBuffer(GLenum _usage, std::size_t length, const void* data)
	{
		bind();
		ibo = VertexBuffer(GL_ELEMENT_ARRAY_BUFFER, _usage, length, data);
		ibo.bind();
	}

	void RenderObject::bindAttribute(int attribute, unsigned int buffer_id, GLenum type, unsigned int count, unsigned int stride, intptr_t offset)
	{
		bind();
		buffers.at(buffer_id).bind();
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

	RenderObject::RenderObject(const RenderObject& copy)
	{
		vao = copy.vao;
		buffers = copy.buffers;
		ibo = copy.ibo;
	}

	RenderObject::~RenderObject()
	{

	}

	// Buffer Object

	BufferObject::BufferObject()
	{
		type = target = usage = 0;
		vertex_count = 0;
	}

	BufferObject::BufferObject(std::map<int, int> topology, GLenum _type, GLenum _target, GLenum _usage) : BufferObject()
	{
		type = _type;
		target = _target;
		usage = _usage;

		va.init();
		buffer.init(target, usage);

		int sum = 0;
		int offset = 0;

		for (auto t : topology)
		{
			sum += t.second;
		}

		for (auto t : topology)
		{
			va.bindAttribute(t.first, buffer, type, t.second, sum * sizeof(float), offset);
			offset += t.second * sizeof(float);
		}

		buffer.unbind();
		va.unbind();
	}

	void BufferObject::setData(std::size_t length, const void* data)
	{
		buffer.setData(length, data);
	}

	void BufferObject::setSubData(std::size_t pointer, std::size_t length, const void* data)
	{
		buffer.setSubData(pointer, length, data);
	}

	void BufferObject::bind()
	{
		va.bind();
	}

	void BufferObject::unbind()
	{
		va.unbind();
	}

	void BufferObject::setVertexCount(unsigned long _vertex_count)
	{
		vertex_count = _vertex_count;
	}

	BufferObject::~BufferObject()
	{
		glDeleteBuffers(1, &buffer);
	}

	*/

	/* Frame Buffer Object */

	FrameBuffer::FrameBuffer()
	{
		width = 0;
		height = 0;
		id = 0;
		depth_buffer_id = 0;
		texture_id = 0;
	}

	bool FrameBuffer::create(int _width, int _height)
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
			log("Framebuffer", "Failed to create the frame buffer");
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

};