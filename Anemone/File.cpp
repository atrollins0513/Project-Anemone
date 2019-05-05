#include "File.h"

namespace Anemone
{
	std::string LoadFile(std::string filename, AE_INT file_mode)
	{
		std::ifstream file(filename, file_mode);

		std::string data;

		if (file.is_open())
		{
			file.seekg(0, std::ios::end);
			AE_UINT size = file.tellg();
			file.seekg(0, std::ios::beg);

			if (size <= 0)
			{
				file.close();
				return "";
			}

			AE_CHAR* fileData = new char[size + 1];
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
};