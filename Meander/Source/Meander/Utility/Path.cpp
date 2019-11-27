#include "pch.h"
#include "Path.h"
#include <direct.h>

#define IS_PATH_DELIMITER(x) x == '\\' || x == '/'

namespace Meander
{
	std::string Path::GetDirectory(const std::string& path)
	{
		size_t ext = path.find('.');

		// If there is no extension, we assume the path is already a directory
		if (ext == std::string::npos)
			return std::string(path);

		size_t delimiter = path.find_last_of('/');
		if (delimiter != std::string::npos)
			return path.substr(0, delimiter + 1);

		delimiter = path.find_last_of('\\');
		if (delimiter != std::string::npos)
			return path.substr(0, delimiter + 1);

		return std::string(path);
	}

	std::string Path::Clean(const std::string& path)
	{
		std::string result(path);

		bool isDirectory = true;
		for (size_t i = 0; i < result.length(); i++)
		{
			// Replace backslashes
			if (result[i] == '\\')
				result[i] = '/';

			// Remove multiple slashes
			if (i > 0 && result[i] == '/' && result[i - (size_t)1] == '/')
				result.erase(i, 1);

			// If the path contains an extension, it's a file
			if (result[i] == '.')
				isDirectory = false;
		}

		// Add trailing slash to directory
		if (!result.empty() && isDirectory && result[result.length() - 1] != '/')
			result += '/';

		return result;
	}

	std::string Path::Combine(const std::string& a, const std::string& b)
	{
		std::string result;

		result.append(a);
		result.append(b);

		return Clean(result);
	}

	std::string Path::GetWorkingDirectory()
	{
		static char buffer[256];

#pragma warning(suppress: 6031)
		_getcwd(buffer, 256);

		return std::string(buffer);
	}
}