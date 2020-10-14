#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Meander
{
	class Log
	{
	public:
		inline static std::shared_ptr<spdlog::logger>& Get() { return s_Logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
		static std::shared_ptr<spdlog::logger> Create();
	};
}

#define MN_TRACE(...) ::Meander::Log::Get()->trace(__VA_ARGS__)
#define MN_INFO(...) ::Meander::Log::Get()->info(__VA_ARGS__)
#define MN_WARN(...) ::Meander::Log::Get()->warn(__VA_ARGS__)
#define MN_ERROR(...) ::Meander::Log::Get()->error(__VA_ARGS__)
#define MN_CRITICAL(...) ::Meander::Log::Get()->critical(__VA_ARGS__)