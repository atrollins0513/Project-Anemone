#include "ParticleManager.h"

namespace Anemone
{
	namespace Manager
	{

		ParticleManager::ParticleManager()
		{
			
		}

		void ParticleManager::Create()
		{
			pos.Init(GL_ARRAY_BUFFER, GL_STREAM_DRAW);
			tex.Init(GL_ARRAY_BUFFER, GL_STREAM_DRAW);
			color.Init(GL_ARRAY_BUFFER, GL_STREAM_DRAW);
			vao.Generate();
			vao.BindAttribute(0, pos, GL_FLOAT, 3, 36, 0);
			vao.BindAttribute(1, pos, GL_FLOAT, 2, 36, 12);
			vao.BindAttribute(2, pos, GL_FLOAT, 4, 36, 20);
		}

		void ParticleManager::Update(AE_DOUBLE dt)
		{
			for (auto e : emitters)
			{
				if (e.second->Update(dt))
				{
					particles.push_back(e.second->CreateParticle());
				}
			}

			float* vertices = new float[particles.size() * 54];
			unsigned int i = 0;
			//std::vector<AE_FLOAT> pos_coord;
			//std::vector<AE_FLOAT> tex_coord;
			//std::vector<AE_FLOAT> color_coord;
			unsigned int number_of_particles = 0;

			AE_FLOAT x, y, z, r, g, b, a, u, v, u_width, v_height, width, height;

			auto p = std::begin(particles);

			while (p != std::end(particles))
			{
				p->age += dt;
				if (p->age < p->life_limit)
				{
					p->pos.x += p->vel.x * dt;
					p->pos.y += p->vel.y * dt;

					x = p->pos.x;
					y = p->pos.y;
					z = p->pos.z;
					r = p->color.r;
					g = p->color.g;
					b = p->color.b;
					a = p->color.a;
					u = p->u;
					v = p->v;
					u_width = p->u_width;
					v_height = p->v_height;
					width = p->width;
					height = p->height;

					vertices[i + 0]  = x; vertices[i + 1]  = y; vertices[i + 2]  = 0.0f;
					vertices[i + 3]  = u; vertices[i + 4]  = v + v_height;
					vertices[i + 5]  = r; vertices[i + 6]  = g; vertices[i + 7]  = b; vertices[i + 8]  = a;

					vertices[i + 9]  = x + width; vertices[i + 10] = y + height; vertices[i + 11] = 0.0f;
					vertices[i + 12] = u + u_width; vertices[i + 13] = v;
					vertices[i + 14] = r; vertices[i + 15] = g; vertices[i + 16] = b; vertices[i + 17] = a;

					vertices[i + 18] = x; vertices[i + 19] = y + height; vertices[i + 20] = 0.0f;
					vertices[i + 21] = u; vertices[i + 22] = v;
					vertices[i + 23] = r; vertices[i + 24] = g; vertices[i + 25] = b; vertices[i + 26] = a;

					vertices[i + 27] = x; vertices[i + 28] = y; vertices[i + 29] = 0.0f;
					vertices[i + 30] = u; vertices[i + 31] = v + v_height;
					vertices[i + 32] = r; vertices[i + 33] = g; vertices[i + 34] = b; vertices[i + 35] = a;

					vertices[i + 36] = x + width; vertices[i + 37] = y; vertices[i + 38] = 0.0f;
					vertices[i + 39] = u + u_width; vertices[i + 40] = v + v_height;
					vertices[i + 41] = r; vertices[i + 42] = g; vertices[i + 43] = b; vertices[i + 44] = a;

					vertices[i + 45] = x + width; vertices[i + 46] = y + height; vertices[i + 47] = 0.0f;
					vertices[i + 48] = u + u_width; vertices[i + 49] = v;
					vertices[i + 50] = r; vertices[i + 51] = g; vertices[i + 52] = b; vertices[i + 53] = a;

					/*
					pos_coord.push_back(x); pos_coord.push_back(y); pos_coord.push_back(z);
					pos_coord.push_back(x + p->width); pos_coord.push_back(y + p->height); pos_coord.push_back(z);
					pos_coord.push_back(x); pos_coord.push_back(y + p->height); pos_coord.push_back(z);

					pos_coord.push_back(x); pos_coord.push_back(y); pos_coord.push_back(z);
					pos_coord.push_back(x + p->width); pos_coord.push_back(y); pos_coord.push_back(z);
					pos_coord.push_back(x + p->width); pos_coord.push_back(y + p->height); pos_coord.push_back(z);

					tex_coord.push_back(p->u); tex_coord.push_back(p->v + p->v_height);
					tex_coord.push_back(p->u + p->u_width); tex_coord.push_back(p->v);
					tex_coord.push_back(p->u); tex_coord.push_back(p->v);

					tex_coord.push_back(p->u); tex_coord.push_back(p->v + p->v_height);
					tex_coord.push_back(p->u + p->u_width); tex_coord.push_back(p->v + p->v_height);
					tex_coord.push_back(p->u + p->u_width); tex_coord.push_back(p->v);

					color_coord.push_back(p->color.r); color_coord.push_back(p->color.g); color_coord.push_back(p->color.b); color_coord.push_back(p->color.a);
					color_coord.push_back(p->color.r); color_coord.push_back(p->color.g); color_coord.push_back(p->color.b); color_coord.push_back(p->color.a);
					color_coord.push_back(p->color.r); color_coord.push_back(p->color.g); color_coord.push_back(p->color.b); color_coord.push_back(p->color.a);

					color_coord.push_back(p->color.r); color_coord.push_back(p->color.g); color_coord.push_back(p->color.b); color_coord.push_back(p->color.a);
					color_coord.push_back(p->color.r); color_coord.push_back(p->color.g); color_coord.push_back(p->color.b); color_coord.push_back(p->color.a);
					color_coord.push_back(p->color.r); color_coord.push_back(p->color.g); color_coord.push_back(p->color.b); color_coord.push_back(p->color.a);
					*/

					number_of_particles++;
					++p;
					i += 54;
				}
				else
				{
					p = particles.erase(p);
				}
			}

			if (number_of_particles > 0)
			{
				//pos.SetData(pos_coord.size() * sizeof(AE_FLOAT), &pos_coord.at(0));
				//tex.SetData(tex_coord.size() * sizeof(AE_FLOAT), &tex_coord.at(0));
				//color.SetData(color_coord.size() * sizeof(AE_FLOAT), &color_coord.at(0));
				pos.SetData(number_of_particles * 54 * sizeof(AE_FLOAT), vertices);
			}
			delete vertices;
		}

		void ParticleManager::Render()
		{
			vao.bind();

			glDrawArrays(GL_TRIANGLES, 0, particles.size() * 6);

			vao.unbind();
		}

		void ParticleManager::AddEmitter(int id, std::shared_ptr<Emitter> emitter)
		{
			emitters[id] = emitter;
		}

		void ParticleManager::DeleteEmitter(int id)
		{
			if (emitters[id])
				emitters.erase(id);
		}

	};
};