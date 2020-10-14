#include "pch.h"
#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Meander
{
	std::shared_ptr<spdlog::logger> Log::s_Logger = Create();

	std::shared_ptr<spdlog::logger> Log::Create()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		auto logger = spdlog::stdout_color_mt("MEANDER");
		logger->set_level(spdlog::level::trace);

		return logger;
	}
}
