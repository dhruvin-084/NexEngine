#ifndef LOG_H_
#define LOG_H_

#include<memory>
#include<spdlog/spdlog.h>
#include<spdlog/sinks/stdout_color_sinks.h>
#include"Core.h"

namespace Nex {

	class NEX_API Log {
	public:
		static void Init();
		
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}


// core logger macros
#define NEX_CORE_TRACE(...)      ::Nex::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NEX_CORE_INFO(...)       ::Nex::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NEX_CORE_WARN(...)       ::Nex::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NEX_CORE_ERROR(...)      ::Nex::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NEX_CORE_FATAL(...)      ::Nex::Log::GetCoreLogger()->fatal(__VA_ARGS__)


// client logger macros
#define NEX_TRACE(...)           ::Nex::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NEX_INFO(...)            ::Nex::Log::GetClientLogger()->info(__VA_ARGS__)
#define NEX_WARN(...)            ::Nex::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NEX_ERROR(...)           ::Nex::Log::GetClientLogger()->error(__VA_ARGS__)
#define NEX_FATAL(...)           ::Nex::Log::GetClientLogger()->fatal(__VA_ARGS__)


#endif // !LOG_H_

