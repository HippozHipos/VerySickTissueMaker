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

#define BDLOG_CON_INFO(...)       SPDLOG_LOGGER_INFO(be::Logger::Console(), __VA_ARGS__)
#define BDLOG_CON_WARN(...)       SPDLOG_LOGGER_WARN(be::Logger::Console(), __VA_ARGS__)
#define BDLOG_CON_ERR(...)        SPDLOG_LOGGER_ERROR(be::Logger::Console(), __VA_ARGS__)
#define BDLOG_CON_CRIT(...)       SPDLOG_LOGGER_CRITICAL(be::Logger::Console(), __VA_ARGS__)
		 
#define BDLOG_TRC_INFO(...)      SPDLOG_LOGGER_INFO(be::Logger::Trace(), __VA_ARGS__)
#define BDLOG_TRC_WARN(...)      SPDLOG_LOGGER_WARN(be::Logger::Trace(), __VA_ARGS__)
#define BDLOG_TRC_ERR(...)       SPDLOG_LOGGER_ERROR(be::Logger::Trace(), __VA_ARGS__)
#define BDLOG_TRC_CRIT(...)      SPDLOG_LOGGER_CRITICAL(be::Logger::Trace(), __VA_ARGS__)
		
#define BDLOG_DBG_INFO(...)      SPDLOG_LOGGER_INFO(be::Logger::Debug(), __VA_ARGS__)
#define BDLOG_DBG_WARN(...)      SPDLOG_LOGGER_WARN(be::Logger::Debug(), __VA_ARGS__)
#define BDLOG_DBG_ERR(...)       SPDLOG_LOGGER_ERROR(be::Logger::Debug(), __VA_ARGS__)
#define BDLOG_DBG_CRIT(...)      SPDLOG_LOGGER_CRITICAL(be::Logger::Debug(), __VA_ARGS__)
		
#define BDLOG_CD_INFO(...)       SPDLOG_LOGGER_INFO(be::Logger::Console(), __VA_ARGS__);     SPDLOG_LOGGER_INFO(be::Logger::Debug(), __VA_ARGS__)
#define BDLOG_CD_WARN(...)       SPDLOG_LOGGER_WARN(be::Logger::Console(), __VA_ARGS__);     SPDLOG_LOGGER_WARN(be::Logger::Debug(), __VA_ARGS__)
#define BDLOG_CD_ERR(...)        SPDLOG_LOGGER_ERROR(be::Logger::Console(), __VA_ARGS__);    SPDLOG_LOGGER_ERROR(be::Logger::Debug(), __VA_ARGS__)
#define BDLOG_CD_CRIT(...)       SPDLOG_LOGGER_CRITICAL(be::Logger::Console(), __VA_ARGS__); SPDLOG_LOGGER_CRITICAL(be::Logger::Debug(), __VA_ARGS__)