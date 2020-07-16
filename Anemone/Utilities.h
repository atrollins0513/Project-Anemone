#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <random>
#include <time.h>

#include "Math.h"

namespace ae
{

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