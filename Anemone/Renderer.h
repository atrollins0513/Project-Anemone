#pragma once

#include <memory>
#include <string>

#include "BufferObject.h"
#include "Texture.h"
#include "Shader.h"
#include "ResourceManager.h"

namespace ae
{
	struct Vertex
	{
		ae::vec3 pos;

		#ifndef AE_VERTEX_DISABLE_TEX
				ae::vec2 tex;
		#endif

		#ifndef AE_VERTEX_DISABLE_COLOR
				ae::vec3 color;
		#endif

		#if defined AE_VERTEX_ENABLE_NORMAL
				ae::vec3 normal;
		#endif
	};

    template<typename ObjectClass, typename VertexClass>
    class RendererInterface
    {
    public:

        RendererInterface() = default;

        RendererInterface(int maxNumberOfVertices, BufferObject _buffer) : RendererInterface()
        {
            init(maxNumberOfVertices, _buffer);
        }

        void init(int maxNumberOfVertices, BufferObject _buffer)
        {
            base = new VertexClass[maxNumberOfVertices];
            ptr = base;
            buffer = _buffer;
            buffer->setData(sizeof(VertexClass), maxNumberOfVertices, nullptr);
        }

        void updateBuffer()
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)ptr - (uint8_t*)base);
            buffer->setSubData(0, dataSize, base);
            vertexCount = dataSize / sizeof(VertexClass);
        }

        virtual void add(const ObjectClass& o) = 0;

        virtual void render() = 0;

        void reset() { ptr = base; }

        void begin() { reset(); }

        void end() { updateBuffer(); }

        VertexClass* getBufferBase() { return base; }

        VertexClass* getBufferPtr() {  return ptr; }

        ae::BufferObject* getBuffer() { return buffer; }

        std::size_t getVertexCount() { return vertexCount; }

        ~RendererInterface()
        {
            delete base;
            delete ptr;
        }

    protected:

        VertexClass* base       { nullptr };
        VertexClass* ptr        { nullptr };
        std::size_t vertexCount { 0 };
        BufferObject buffer;

    };
};