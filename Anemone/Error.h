#pragma once

#include "Anemone.h"

#include <time.h>
#include <string>
#include <fstream>
#include <Windows.h>

namespace Anemone
{
	namespace Error
	{
		extern void Log(std::string identifier, std::string message);

		extern void Log(std::string identifier, std::string message, std::string message_two);
	};

	#ifdef _MSC_VER
		inline void output(std::string str)
		{
			OutputDebugString(str.c_str());
		}
	#endif
};
