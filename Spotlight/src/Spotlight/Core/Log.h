#pragma once

#include "Spotlight/Core/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Spotlight
{

	class SPOTLIGHT_API Log
	{
	public:
		static void LogInit();
		
		static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return sm_CoreLogger; }
		static std::shared_ptr<spdlog::logger> &GetClientLogger() { return sm_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> sm_CoreLogger;
		static std::shared_ptr<spdlog::logger> sm_ClientLogger;
	};

}

#define SPL_CORE_TRACE(...)	::Spotlight::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SPL_CORE_INFO(...)	::Spotlight::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SPL_CORE_WARN(...)	::Spotlight::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SPL_CORE_ERROR(...)	::Spotlight::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SPL_CORE_FATAL(...)	::Spotlight::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define SPL_TRACE(...)		::Spotlight::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SPL_INFO(...)		::Spotlight::Log::GetClientLogger()->info(__VA_ARGS__)
#define SPL_WARN(...)		::Spotlight::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SPL_ERROR(...)		::Spotlight::Log::GetClientLogger()->error(__VA_ARGS__)
#define SPL_FATAL(...)		::Spotlight::Log::GetClientLogger()->critical(__VA_ARGS__)