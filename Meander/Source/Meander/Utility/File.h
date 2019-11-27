#pragma once

namespace Meander
{
	class File
	{
	public:
		/* Reads all content from a file. */
		static bool Read(const char* path, std::string& content);
	};
}