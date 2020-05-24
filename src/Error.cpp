#include "..\Anemone\Error.h"

namespace Anemone
{
	namespace Error
	{
		void Log(std::string identifier, std::string message)
		{
			std::ofstream file("log.txt", std::ios::out | std::ios::app);
			if (file.is_open())
			{
				time_t rawtime;
				struct tm * timeinfo;
				char buffer[25];
				time(&rawtime);
				timeinfo = localtime(&rawtime);
				strftime(buffer, 25, "[%F %H:%M:%S]", timeinfo);
				file << buffer << "[" << identifier << "]" << "[" << message << "]" << std::endl;
				file.close();
			}
		}

		void Log(std::string identifier, std::string message, std::string message_two)
		{
			std::ofstream file("log.txt", std::ios::out | std::ios::app);
			if (file.is_open())
			{
				time_t rawtime;
				struct tm * timeinfo;
				char buffer[25];
				time(&rawtime);
				timeinfo = localtime(&rawtime);
				strftime(buffer, 25, "[%F %H:%M:%S]", timeinfo);
				file << buffer << "[" << identifier << "]" << "[" << message << message_two << "]" << std::endl;
				file.close();
			}
		}
	};
};