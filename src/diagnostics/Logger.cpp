#include <spdlog/sinks/rotating_file_sink.h>

#include "Logger.h"

namespace vstm {

	std::shared_ptr<spdlog::logger> Logger::s_console = spdlog::stdout_color_mt("VSTM Console");
	std::shared_ptr<spdlog::logger> Logger::s_trace_file = 
		spdlog::rotating_logger_mt("VSTM Trace", "logs/VSTMTrace.txt", 1024 * 1024, 5);
	std::shared_ptr<spdlog::logger> Logger::s_debug_file = 
		spdlog::rotating_logger_mt("VSTM Debug", "logs/VSTMDebug.txt", 1024 * 1024, 5);


	void Logger::Init()
	{
		const char* pattern = "[%D] [%H:%M:%S] [%n]\n[Source: %s]\n[Function: %!] [Line: %#] [Thread: %t]\n%v";
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
