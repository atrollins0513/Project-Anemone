#pragma once

#include <unordered_map>
#include <string>
#include <any>

namespace ae
{
	class ResourceManager
	{
	public:

		ResourceManager() { }

		template<typename T>
		void store(const std::string& name, T t)
		{
			assert(data.find(name) != data.end());
			data.emplace(name, t);
		}

		template<typename T>
		T get(const std::string& name)
		{
			assert(data.find(name) != data.end());
			return std::any_cast<T>(data[name]);
		}

	private:

		std::unordered_map<std::string, std::any> data;

	};
};
