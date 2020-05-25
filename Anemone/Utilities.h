#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

#include "Error.h"

namespace Anemone
{
	extern std::string LoadFile(std::string filename, int file_mode = std::ios::in);
	extern std::vector<std::string> explode(std::string const& s, char delim);
};