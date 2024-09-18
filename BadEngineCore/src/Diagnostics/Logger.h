#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "spdlog/sinks/basic_file_sink.h"

namespace be {

	/*!
	 *	Logger class. This class isn't directly used for logging. Instead the logging macros are used.
	 *  Logging macro has format BELOG_(CON, TRC, DBG, CD)_(INFO, WARN, ERR, CRIT)
	 *  BELOG - It is a bad engine logging macro
	 *	CON - It logs to console
	 *	TRC - It logs to a trace log file
	 *	DBG - It logs to a debug log file
	 *  CD - Log to both console and debug trace file
	 *	INFO, WARN, ERR, CRIT - Log levels
	 *  Arguments - First argument: format, second argument: values
	 *  Example: BELOG_DBG_ERR("The value is {}", 4) - Logs "The value is 4" to dbg trace file.
	 *  String formatting is the same used by fmt library.
	 */

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

#define BELOG_CON_INFO(...)       SPDLOG_LOGGER_INFO(be::Logger::Console(), __VA_ARGS__)
#define BELOG_CON_WARN(...)       SPDLOG_LOGGER_WARN(be::Logger::Console(), __VA_ARGS__)
#define BELOG_CON_ERR(...)        SPDLOG_LOGGER_ERROR(be::Logger::Console(), __VA_ARGS__)
#define BELOG_CON_CRIT(...)       SPDLOG_LOGGER_CRITICAL(be::Logger::Console(), __VA_ARGS__)
		 
#define BELOG_TRC_INFO(...)      SPDLOG_LOGGER_INFO(be::Logger::Trace(), __VA_ARGS__)
#define BELOG_TRC_WARN(...)      SPDLOG_LOGGER_WARN(be::Logger::Trace(), __VA_ARGS__)
#define BELOG_TRC_ERR(...)       SPDLOG_LOGGER_ERROR(be::Logger::Trace(), __VA_ARGS__)
#define BELOG_TRC_CRIT(...)      SPDLOG_LOGGER_CRITICAL(be::Logger::Trace(), __VA_ARGS__)
		
#define BELOG_DBG_INFO(...)      SPDLOG_LOGGER_INFO(be::Logger::Debug(), __VA_ARGS__)
#define BELOG_DBG_WARN(...)      SPDLOG_LOGGER_WARN(be::Logger::Debug(), __VA_ARGS__)
#define BELOG_DBG_ERR(...)       SPDLOG_LOGGER_ERROR(be::Logger::Debug(), __VA_ARGS__)
#define BELOG_DBG_CRIT(...)      SPDLOG_LOGGER_CRITICAL(be::Logger::Debug(), __VA_ARGS__)
		
#define BELOG_CD_INFO(...)       SPDLOG_LOGGER_INFO(be::Logger::Console(), __VA_ARGS__);     SPDLOG_LOGGER_INFO(be::Logger::Debug(), __VA_ARGS__)
#define BELOG_CD_WARN(...)       SPDLOG_LOGGER_WARN(be::Logger::Console(), __VA_ARGS__);     SPDLOG_LOGGER_WARN(be::Logger::Debug(), __VA_ARGS__)
#define BELOG_CD_ERR(...)        SPDLOG_LOGGER_ERROR(be::Logger::Console(), __VA_ARGS__);    SPDLOG_LOGGER_ERROR(be::Logger::Debug(), __VA_ARGS__)
#define BELOG_CD_CRIT(...)       SPDLOG_LOGGER_CRITICAL(be::Logger::Console(), __VA_ARGS__); SPDLOG_LOGGER_CRITICAL(be::Logger::Debug(), __VA_ARGS__)