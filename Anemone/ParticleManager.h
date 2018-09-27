#pragma once

#include "Anemone.h"

#include <vector>
#include <memory>
#include <unordered_map>
#include <iostream>

#include "BufferObject.h"
#include "Particle.h"
#include "Emitter.h"

namespace Anemone
{
	namespace Manager
	{
		class ParticleManager
		{
		public:

			ParticleManager();

			void Create();

			void Update(AE_DOUBLE dt);

			void Render();

			void AddEmitter(int id, std::shared_ptr<Emitter> emitter);

			void DeleteEmitter(int id);

		protected:
		private:

			std::unordered_map <int, std::shared_ptr<Emitter>> emitters;

			std::vector<Particle> particles;

			VertexBuffer pos, tex, color;

			VertexArray vao;

		};
	};
};