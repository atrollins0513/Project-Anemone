#pragma once

#include "Anemone.h"

#include <unordered_map>
#include <string>
#include <memory>

#include "Shader.h"
#include "Texture.h"
#include "Error.h"
//#include "Audio.h"
// raw data

namespace Anemone
{

	namespace ResourceManager
	{

		class resource_shader
		{
		public:

			std::shared_ptr<Shader> create(std::string name);
			void unload(std::string name);

			std::shared_ptr<Shader> operator()(std::string name)
			{
				return shaders[name];
			}
				
			std::shared_ptr<Shader>& operator[](std::string name)
			{
				return shaders[name];
			}

		protected:
		private:

			std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;

		};

		class resource_texture
		{
		public:

			std::shared_ptr<Texture> create(std::string name);
			void unload(std::string name);

			auto operator()(std::string name)
			{
				return textures[name];
			}

			auto& operator[](std::string name)
			{
				return textures[name];
			}

		protected:
		private:

			std::unordered_map<std::string, std::shared_ptr<Texture>> textures;

		};

		extern resource_shader shader;
		extern resource_texture texture;
	};

};

#define rm Anemone::ResourceManager
