#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "spdlog/sinks/basic_file_sink.h"

namespace vstm {

	class Logger
	{
	private:
		Logger() = default;

	public:
		static void Init();
		static std::shared_ptr<spdlog::logger> Console();
		static std::shared_ptr<spdlog::logger> Trace();
		static std::shared_ptr<spdlog::logger> Debug();

	private:
		static std::shared_ptr<spdlog::logger> s_console;
		static std::shared_ptr<spdlog::logger> s_trace_file;
		static std::shared_ptr<spdlog::logger> s_debug_file;
	};

}

#define VSTM_CON_LOGINFO(...) vstm::Logger::Console()->info(__VA_ARGS__)
#define VSTM_CON_LOGWARN(...) vstm::Logger::Console()->warn(__VA_ARGS__)
#define VSTM_CON_LOGERROR(...) vstm::Logger::Console()->error(__VA_ARGS__)
#define VSTM_CON_LOGCRITICAL(...) vstm::Logger::Console()->critical(__VA_ARGS__)

#define VSTM_TRACE_LOGINFO(...) vstm::Logger::Trace()->info(__VA_ARGS__)
#define VSTM_TRACE_LOGWARN(...) vstm::Logger::Trace()->warn(__VA_ARGS__)
#define VSTM_TRACE_LOGERROR(...) vstm::Logger::Trace()->error(__VA_ARGS__)
#define VSTM_TRACE_LOGCRITICAL(...) vstm::Logger::Trace()->critical(__VA_ARGS__)

#define VSTM_DEBUG_LOGINFO(...) vstm::Logger::Debug()->info(__VA_ARGS__)
#define VSTM_DEBUG_LOGWARN(...) vstm::Logger::Debug()->warn(__VA_ARGS__)
#define VSTM_DEBUG_LOGERROR(...) vstm::Logger::Debug()->error(__VA_ARGS__)
#define VSTM_DEBUG_LOGCRITICAL(...) vstm::Logger::Debug()->critical(__VA_ARGS__)

#define VSTM_CD_LOGINFO(...)     vstm::Logger::Console()->info(__VA_ARGS__); vstm::Logger::Debug()->info(__VA_ARGS__)
#define VSTM_CD_LOGWARN(...)     vstm::Logger::Console()->warn(__VA_ARGS__); vstm::Logger::Debug()->warn(__VA_ARGS__)
#define VSTM_CD_LOGERROR(...)    vstm::Logger::Console()->error(__VA_ARGS__); vstm::Logger::Debug()->error(__VA_ARGS__)
#define VSTM_CD_LOGCRITICAL(...) vstm::Logger::Console()->critical(__VA_ARGS__); vstm::Logger::Debug()->critical(__VA_ARGS__)
