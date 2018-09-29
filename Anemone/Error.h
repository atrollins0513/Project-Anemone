#pragma once

#include "Anemone.h"

#include <time.h>
#include <string>
#include <fstream>

namespace Anemone
{
	namespace Error
	{
		extern void Log(std::string identifier, std::string message);

		extern void Log(std::string identifier, std::string message, std::string message_two);
	};
};
