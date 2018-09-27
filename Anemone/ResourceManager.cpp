#include "ResourceManager.h"

namespace Anemone
{
	namespace ResourceManager
	{
		resource_shader shader;

		resource_texture texture;

		std::shared_ptr<Shader> resource_shader::create(std::string name)
		{
			if(shaders[name] == nullptr)
			{
				shaders[name] = std::make_shared<Shader>();
				return shaders[name];
			}
			return shaders[name];
		}

		void resource_shader::unload(std::string name)
		{
			if (shaders[name] != nullptr)
				shaders.erase(name);
		}

		std::shared_ptr<Texture> resource_texture::create(std::string name)
		{
			if (textures[name] == nullptr)
			{
				textures[name] = std::make_shared<Texture>();
				return textures[name];
			}
			return textures[name];
		}

		void resource_texture::unload(std::string name)
		{
			if (textures[name] != nullptr)
				textures.erase(name);
		}
	};
};