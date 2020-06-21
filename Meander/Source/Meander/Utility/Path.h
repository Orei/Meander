#pragma once
#include <string>

namespace Meander
{
	class Path
	{
	public:
		static std::string GetDirectory(const std::string& path);
		static std::string Clean(const std::string& path);
		static std::string Combine(const std::string& a, const std::string& b);
		static std::string GetExtension(const std::string& path);
		static std::string GetFileName(const std::string& path, bool extension = true);
		static std::string GetWorkingDirectory();
	};
}