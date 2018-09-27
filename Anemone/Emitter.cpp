#include "Emitter.h"

namespace Anemone
{
	Emitter::Emitter(Particle _root_particle, vec3 _position, AE_FLOAT _direction, AE_FLOAT _spread, AE_FLOAT _speed, AE_FLOAT _partPerSec)
	{
		root_particle = _root_particle;
		position = _position;
		direction = std::round(_direction);
		spread = _spread;
		speed = _speed;
		partPerSec = _partPerSec;
		counter = 0.0;
		stop = false;
	}

	AE_BOOL Emitter::Update(AE_DOUBLE dt)
	{
		counter += dt;
		if (counter >= 1.0f / partPerSec)
		{
			counter = 0.0;
			return !stop;
		}
		return false;
	}

	Particle Emitter::CreateParticle()
	{
		Particle newParticle = root_particle;
		newParticle.pos += position;

		AE_INT direction_offset = (spread >= 2.0f ? Math::random((unsigned int)(spread / 2.0f)) : 0);
		AE_FLOAT newDirection = direction + (Math::random(2) ? direction_offset : -direction_offset);

		newParticle.vel.x = cos(to_radians(newDirection)) * speed;
		newParticle.vel.y = sin(to_radians(newDirection)) * speed;

		return newParticle;
	}

	void Emitter::setPosition(const vec3& newPosition)
	{
		position = newPosition;
	}

	void Emitter::Pause()
	{
		stop = true;
	}

	void Emitter::Start()
	{
		stop = false;
	}
};