#include "pch.h"
#include "File.h"
#include <fstream>
#include <sstream>

namespace Meander
{
	bool File::Read(const char* path, std::string& content)
	{
		std::ifstream stream;
		std::stringstream sstream;

		stream.open(path);
		if (!stream.is_open())
		{
			MN_ERROR("Unable to read file '{0}'.", path);
			return false;
		}

		sstream << stream.rdbuf();
		content = sstream.str();

		return true;
	}
}