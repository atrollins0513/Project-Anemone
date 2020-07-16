#include "..\Anemone\Utilities.h"

namespace ae
{

	void log(std::string identifier, std::string message)
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
			file << buffer << "[" << identifier << "]" << "[" << message << "]" << std::endl;
			file.close();
		}
	}

	void log(std::string identifier, std::string message, std::string message_two)
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
			file << buffer << "[" << identifier << "]" << "[" << message << message_two << "]" << std::endl;
			file.close();
		}
	}

	std::string loadFile(std::string filename, int file_mode)
	{
		std::ifstream file(filename, file_mode);

		std::string data;

		if (file.is_open())
		{
			file.seekg(0, std::ios::end);
			long size = file.tellg();
			file.seekg(0, std::ios::beg);

			if (size <= 0)
			{
				file.close();
				return "";
			}

			char* fileData = new char[size + 1];
			file.read((char*)fileData, size);

			data = fileData;

			delete[] fileData;

			file.close();

			return data;
		}
		else
		{
			log(filename, "Failed to open.");
			return "";
		}
	}

	std::vector<std::string> explode(std::string const& s, char delim)
	{
		std::vector<std::string> result;
		std::istringstream iss(s);

		for (std::string token; std::getline(iss, token, delim); )
		{
			result.push_back(std::move(token));
		}

		return result;
	}

	void setSeed(int seed)
	{
		srand(seed);
	}

	int random(unsigned int upper_limit)
	{
		return rand() % upper_limit;
	}

	int random(unsigned int lower_limit, unsigned int upper_limit)
	{
		return rand() % upper_limit + lower_limit;
	}

};