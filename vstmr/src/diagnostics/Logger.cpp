#include <spdlog/sinks/rotating_file_sink.h>

#include "Logger.h"

namespace be {

	std::shared_ptr<spdlog::logger> Logger::s_console = spdlog::stdout_color_mt("VSTM Console");
	std::shared_ptr<spdlog::logger> Logger::s_trace_file = 
		spdlog::rotating_logger_mt("VSTM Trace", "logs/VSTMTrace.txt", 1024 * 1024, 5);
	std::shared_ptr<spdlog::logger> Logger::s_debug_file = 
		spdlog::rotating_logger_mt("VSTM Debug", "logs/VSTMDebug.txt", 1024 * 1024, 5);


	void Logger::Init()
	{
		const char* pattern = "[VSTMR LOG][%D][%H:%M:%S][%l][%n]\n[Source: %s][Line: %#]\n[Function: %!][Thread: %t]\n%v\n";
		s_console.get()->set_pattern(pattern);
		s_trace_file.get()->set_pattern(pattern);
		s_debug_file.get()->set_pattern(pattern);
	}

	std::shared_ptr<spdlog::logger> Logger::Console()
	{
		return spdlog::get("VSTM Console");
	}

	std::shared_ptr<spdlog::logger> Logger::Trace()
	{
		return spdlog::get("VSTM Trace");
	}

	std::shared_ptr<spdlog::logger> Logger::Debug()
	{
		return spdlog::get("VSTM Debug");
	}

}
