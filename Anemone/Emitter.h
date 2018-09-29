#pragma once

#include "Anemone.h"

#include <iostream>

#include "Particle.h"
#include "Math.h"

namespace Anemone
{
	class Emitter
	{
	public:

		Emitter(Particle _root_particle, vec3 _position, AE_FLOAT _direction, AE_FLOAT _spread, AE_FLOAT _speed, AE_FLOAT _partPerSec);

		AE_BOOL Update(AE_DOUBLE dt);

		virtual Particle CreateParticle();

		void setPosition(const vec3& newPosition);

		void Pause();

		void Start();

	protected:
	private:

		Particle root_particle;

		vec3 position;

		AE_FLOAT direction;

		AE_FLOAT spread;

		AE_FLOAT speed;

		AE_FLOAT life;

		AE_FLOAT partPerSec;

		AE_DOUBLE counter;

		AE_BOOL stop;

	};
};
