#include "Renderer.h"

namespace Anemone
{

	Renderer::Renderer(std::string shader_name, std::string texture_name, std::shared_ptr<VertexArray> _vao, RenderInfo ri)
	{
		shader = rm::shader(shader_name);
		texture = rm::texture(texture_name);
		AddVertexArray(_vao);
		SetRenderInfo(ri);
	}

	void Renderer::Render()
	{
		shader->bind();
		texture->bind();
		for (auto v : vao)
		{
			v->bind();

			if (ri.use_indices)
			{
				glDrawElements(ri.mode, ri.count, ri.type, ri.indices);
			}
			else
			{
				glDrawArrays(ri.mode, ri.first, ri.count);
			}

			v->unbind();
		}
		texture->unbind();
		shader->unbind();
	}

	void Renderer::AddVertexArray(std::shared_ptr<VertexArray> _vao)
	{
		vao.push_back(_vao);
	}

	void Renderer::SetRenderInfo(RenderInfo _ri)
	{
		ri = _ri;
	}

};