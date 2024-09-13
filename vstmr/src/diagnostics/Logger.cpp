#include <spdlog/sinks/rotating_file_sink.h>

#include "Logger.h"

namespace be {

	std::shared_ptr<spdlog::logger> Logger::s_console = spdlog::stdout_color_mt("BE Console");
	std::shared_ptr<spdlog::logger> Logger::s_trace_file = 
		spdlog::rotating_logger_mt("BE Trace", "logs/BE_Trace.txt", 1024 * 1024, 5);
	std::shared_ptr<spdlog::logger> Logger::s_debug_file = 
		spdlog::rotating_logger_mt("BE Debug", "logs/BE_Debug.txt", 1024 * 1024, 5);


	void Logger::Init()
	{
		const char* pattern = "[BE LOG][%D][%H:%M:%S][%l][Thread: %t]\n%v";
		s_console.get()->set_pattern(pattern);
		s_trace_file.get()->set_pattern(pattern);
		s_debug_file.get()->set_pattern(pattern);
	}

	std::shared_ptr<spdlog::logger> Logger::Console()
	{
		return spdlog::get("BE Console");
	}

	std::shared_ptr<spdlog::logger> Logger::Trace()
	{
		return spdlog::get("BE Trace");
	}

	std::shared_ptr<spdlog::logger> Logger::Debug()
	{
		return spdlog::get("BE Debug");
	}
}
