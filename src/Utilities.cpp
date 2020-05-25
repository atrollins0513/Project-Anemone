#include "..\Anemone\Utilities.h"

namespace Anemone
{
	std::string LoadFile(std::string filename, int file_mode)
	{
		std::ifstream file(filename, file_mode);

		std::string data;

		if (file.is_open())
		{
			file.seekg(0, std::ios::end);
			unsigned int size = file.tellg();
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
			Error::Log(filename, "Failed to open.");
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
};