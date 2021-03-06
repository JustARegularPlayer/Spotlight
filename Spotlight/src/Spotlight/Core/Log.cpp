#include "splpch.h"
#include "Log.h"

namespace Spotlight
{
	std::shared_ptr<spdlog::logger> Log::sm_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::sm_ClientLogger;

	void Log::LogInit()
	{
		spdlog::set_pattern("[%T] %^%n: %v%$");

		sm_CoreLogger = spdlog::stdout_color_mt("SPOTLIGHT");
		sm_CoreLogger->set_level(spdlog::level::trace);

		sm_ClientLogger = spdlog::stdout_color_mt("CLIENT");
		sm_ClientLogger->set_level(spdlog::level::trace);
	}

}
