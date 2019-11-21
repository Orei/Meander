#include "pch.h"
#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Meander
{
	std::shared_ptr<spdlog::logger> Log::s_Logger;

	void Log::Initialize()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_Logger = spdlog::stdout_color_mt("MEANDER");
		s_Logger->set_level(spdlog::level::trace);
	}
}