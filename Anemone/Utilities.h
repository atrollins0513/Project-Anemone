#pragma once

#include <fstream>
#include <string>

#include "Error.h"

namespace Anemone
{
	extern std::string LoadFile(std::string filename, int file_mode = std::ios::in);
};