#include "..\Anemone\Particle.h"

namespace ae
{

	// Emitter //

	bool Emitter::update(double dt)
	{
		if (disabled) { return false; }
		timer += dt;
		clock += dt;
		if (timer >= emit_rate) {
			timer = 0.0;
			return true;
		}
		return false;
	}

	// Particle System //

	ParticleSystem::ParticleSystem(unsigned int _max_particles) : ParticleSystem()
	{
		max_particles = _max_particles;

		buffer = ae::BufferObject({ {0, 2}, {1, 2}, {2, 3} });
		buffer.setData(max_particles * sizeof(ParticleVertex) * 4u, nullptr);

		base = new ParticleVertex[max_particles * 4]();
		ptr = base;

		indices = new unsigned int[max_particles * 6];
		for (unsigned int i = 0; i < max_particles; ++i)
		{
			indices[i * 6 + 0] = i * 4 + 0;
			indices[i * 6 + 1] = i * 4 + 1;
			indices[i * 6 + 2] = i * 4 + 2;
			indices[i * 6 + 3] = i * 4 + 0;
			indices[i * 6 + 4] = i * 4 + 2;
			indices[i * 6 + 5] = i * 4 + 3;
		}

		buffer.bind();
		index_buffer.init(GL_ELEMENT_ARRAY_BUFFER, GL_UNSIGNED_INT, GL_STATIC_DRAW);
		index_buffer.setData(sizeof(unsigned int), 6 * max_particles, indices);
	}

	void ParticleSystem::add(Particle* p)
	{
		if (particles.size() + queue.size() < max_particles) {
			queue.push_back(p);
		}
	}

	void ParticleSystem::attach(Emitter* emitter)
	{
		toss(std::find(emitters.begin(), emitters.end(), emitter) != emitters.end(), "Emitter has already been attached to this particle system.");
		emitters.push_back(emitter);
	}

	void ParticleSystem::remove(Emitter* emitter)
	{
		auto it = std::find(emitters.begin(), emitters.end(), emitter);
		toss(it != emitters.end(), "This emitter has not been attached to the particle system.");
		emitters.erase(it);
	}

	void ParticleSystem::update(double dt)
	{
		ptr = base;
		float s, c;

		// Call all Emitters and see if any particles need to be added to the system
		for (auto& e : emitters)
		{
			if (e->update(dt)) {
				e->emit(this);
			}
		}

		for (auto particle = particles.begin(); particle != particles.end();)
		{
			Particle* p = (*particle);

			s = sinf(p->angle);
			c = cosf(p->angle);

			if (p->update(s, c, dt) == false) { delete p; particle = particles.erase(particle); }
			else
			{
				for (int i = 0; i < 4; ++i)
				{
					ptr->pos.x = (p->rotate ? (c * offsets[i][0] - s * offsets[i][1]) : offsets[i][0]) * p->size * p->scale + p->pos.x;
					ptr->pos.y = (p->rotate ? (c * offsets[i][1] + s * offsets[i][0]) : offsets[i][1]) * p->size * p->scale + p->pos.y;
					ptr->tex.x = p->tex.x + (tex_offsets[i][0] * p->size);
					ptr->tex.y = p->tex.y + (tex_offsets[i][1] * p->size);
					ptr->color = p->color;
					ptr++;
				}
				particle++;
			}
		}

		for (auto p : queue) {
			particles.push_back(p);
		}
		queue.clear();

		buffer.setSubData(0, (unsigned int)((unsigned long long)ptr - (unsigned long long)base), base);
	}

	void ParticleSystem::render()
	{
		buffer.bind();
		glDrawElements(GL_TRIANGLES, (int)(particles.size() * 6), GL_UNSIGNED_INT, 0);
		buffer.unbind();
	}

	ParticleSystem::ParticleSystem(const ParticleSystem& other)
	{
		base = new ParticleVertex[other.max_particles * 4];
		ptr = base;
		indices = new unsigned int[other.max_particles * 6];
		memcpy(indices, other.indices, other.max_particles * 6 * sizeof(unsigned int));
		buffer = other.buffer;
		index_buffer = other.index_buffer;
		particles = other.particles;
	}

	ParticleSystem::~ParticleSystem()
	{
		delete[] base;
		delete[] indices;
		base = nullptr;
		ptr = nullptr;
		indices = nullptr;
	}
};