#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "spdlog/sinks/basic_file_sink.h"

namespace be {

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

#define VSTM_CON_LOGINFO(...)       SPDLOG_LOGGER_INFO(be::Logger::Console(), __VA_ARGS__)
#define VSTM_CON_LOGWARN(...)       SPDLOG_LOGGER_WARN(be::Logger::Console(), __VA_ARGS__)
#define VSTM_CON_LOGERROR(...)      SPDLOG_LOGGER_ERROR(be::Logger::Console(), __VA_ARGS__)
#define VSTM_CON_LOGCRITICAL(...)   SPDLOG_LOGGER_CRITICAL(be::Logger::Console(), __VA_ARGS__)

#define VSTM_TRACE_LOGINFO(...)     SPDLOG_LOGGER_INFO(be::Logger::Trace(), __VA_ARGS__)
#define VSTM_TRACE_LOGWARN(...)     SPDLOG_LOGGER_WARN(be::Logger::Trace(), __VA_ARGS__)
#define VSTM_TRACE_LOGERROR(...)    SPDLOG_LOGGER_ERROR(be::Logger::Trace(), __VA_ARGS__)
#define VSTM_TRACE_LOGCRITICAL(...) SPDLOG_LOGGER_CRITICAL(be::Logger::Trace(), __VA_ARGS__)

#define VSTM_DEBUG_LOGINFO(...)     SPDLOG_LOGGER_INFO(be::Logger::Debug(), __VA_ARGS__)
#define VSTM_DEBUG_LOGWARN(...)     SPDLOG_LOGGER_WARN(be::Logger::Debug(), __VA_ARGS__)
#define VSTM_DEBUG_LOGERROR(...)    SPDLOG_LOGGER_ERROR(be::Logger::Debug(), __VA_ARGS__)
#define VSTM_DEBUG_LOGCRITICAL(...) SPDLOG_LOGGER_CRITICAL(be::Logger::Debug(), __VA_ARGS__)

#define VSTM_CD_LOGINFO(...)     SPDLOG_LOGGER_INFO(be::Logger::Console(), __VA_ARGS__);     SPDLOG_LOGGER_INFO(be::Logger::Debug(), __VA_ARGS__)
#define VSTM_CD_LOGWARN(...)     SPDLOG_LOGGER_WARN(be::Logger::Console(), __VA_ARGS__);     SPDLOG_LOGGER_WARN(be::Logger::Debug(), __VA_ARGS__)
#define VSTM_CD_LOGERROR(...)    SPDLOG_LOGGER_ERROR(be::Logger::Console(), __VA_ARGS__);    SPDLOG_LOGGER_ERROR(be::Logger::Debug(), __VA_ARGS__)
#define VSTM_CD_LOGCRITICAL(...) SPDLOG_LOGGER_CRITICAL(be::Logger::Console(), __VA_ARGS__); SPDLOG_LOGGER_CRITICAL(be::Logger::Debug(), __VA_ARGS__)
