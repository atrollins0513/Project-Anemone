#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <random>
#include <time.h>
#include <memory>

#include "Math.h"

namespace ae
{

	template<typename T>
	using sptr = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr sptr<T> makeShared(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using uptr = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr uptr<T> makeUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	extern void log(std::string identifier, std::string message);

	extern void log(std::string identifier, std::string message, std::string message_two);

	extern std::string loadFile(std::string filename, int file_mode = std::ios::in);

	extern std::vector<std::string> explode(std::string const& s, char delim);

	extern void setSeed(int seed);

	extern int random(unsigned int upper_limit);

	extern int random(unsigned int lower_limit, unsigned int upper_limit);

	constexpr vec3 hexToRGB(int hex)
	{
		return vec3(((hex >> 16) & 0xFF) / 255.0f, ((hex >> 8) & 0xFF) / 255.0f, (hex & 0xFF) / 255.0f);
	}

};