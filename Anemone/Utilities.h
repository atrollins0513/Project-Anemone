#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <random>

#include "Error.h"
#include "Math.h"

namespace Anemone
{
	extern std::string LoadFile(std::string filename, int file_mode = std::ios::in);

	extern std::vector<std::string> explode(std::string const& s, char delim);

	extern void setSeed(int seed);

	extern int random(unsigned int upper_limit);

	extern int random(unsigned int lower_limit, unsigned int upper_limit);

	extern vec3 hexToRGB(std::string hex);
};