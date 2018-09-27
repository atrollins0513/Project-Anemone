#pragma once

#include "Anemone.h"

#include <fstream>
#include <string>

#include "Error.h"

namespace Anemone
{
	extern std::string LoadFile(std::string filename, AE_INT file_mode = std::ios::in);
};
