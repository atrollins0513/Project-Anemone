#include "..\Anemone\Error.h"

void log(const std::string& identifier, const std::string& message)
{
	std::ofstream file("log.txt", std::ios::out | std::ios::app);
	if (file.is_open())
	{
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[25];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 25, "[%F %H:%M:%S]", timeinfo);
		file << buffer << "[" << identifier << "]\n" << "[" << message << "]" << std::endl;
		file.close();
	}
}

void log(const std::string& identifier, const std::string& message, const std::string& message_two)
{
	std::ofstream file("log.txt", std::ios::out | std::ios::app);
	if (file.is_open())
	{
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[25];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 25, "[%F %H:%M:%S]", timeinfo);
		file << buffer << "[" << identifier << "]\n" << "[" << message << message_two << "]" << std::endl;
		file.close();
	}
}

bool toss(bool trigger, const std::string& msg)
{
if (trigger) {
#ifndef AE_HIDE_DEBUG_CONSOLE
	std::cout << msg << "\n";
#endif
throw std::runtime_error(msg);
}
return trigger;
}