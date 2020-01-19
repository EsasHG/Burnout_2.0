#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Burnout
{

class BURNOUT_API Log
{

public: 
	static void Init();
	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
private:
	static std::shared_ptr<spdlog::logger> s_CoreLogger;
	static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

}


//Core log macros
#define BO_CORE_TRACE(...) ::Burnout::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BO_CORE_INFO(...)  ::Burnout::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BO_CORE_WARN(...)  ::Burnout::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BO_CORE_ERROR(...) ::Burnout::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BO_CORE_FATAL(...) ::Burnout::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define BO_TRACE(...)	   ::Burnout::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BO_INFO(...)	   ::Burnout::Log::GetClientLogger()->info(__VA_ARGS__)
#define BO_WARN(...)	   ::Burnout::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BO_ERROR(...)	   ::Burnout::Log::GetClientLogger()->error(__VA_ARGS__)
#define BO_FATAL(...)      ::Burnout::Log::GetClientLogger()->fatal(__VA_ARGS__)