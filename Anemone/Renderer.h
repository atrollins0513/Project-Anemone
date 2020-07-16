#pragma once

#include <memory>
#include <string>

#include "BufferObject.h"
#include "Texture.h"
#include "Shader.h"
#include "ResourceManager.h"

namespace ae
{
	struct RenderInfo
	{

		GLenum mode;

		GLint first;

		GLsizei count;

		void* indices;

		GLenum type;

		bool use_indices;

		RenderInfo()
		{
			mode = first = count = type = 0;
			indices = nullptr;
			use_indices = false;
		}

		RenderInfo(GLenum _mode, GLint _first, GLsizei _count)
		{
			mode = _mode;
			first = _first;
			count = _count;
			use_indices = false;
			indices = nullptr;
			type = 0;
		}

		RenderInfo(GLenum _mode, GLsizei _count, GLenum _type, void* _indices)
		{
			mode = _mode;
			first = 0;
			count = _count;
			use_indices = true;
			indices = _indices;
			type = _type;
		}

	};

	class Renderer
	{
	public:
		
		Renderer(std::string shader_name, std::string texture_name, std::shared_ptr<VertexArray> _vao, RenderInfo ri);

		void Render();

		void AddVertexArray(std::shared_ptr<VertexArray> _vao);

		void SetRenderInfo(RenderInfo _ri);

	protected:
	private:

		std::vector<std::shared_ptr<VertexArray>> vao;

		std::shared_ptr<Texture> texture;

		std::shared_ptr<Shader> shader;

		RenderInfo ri;

	};
};