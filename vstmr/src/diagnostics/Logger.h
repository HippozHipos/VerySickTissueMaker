#pragma once
#include "pch.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "spdlog/sinks/basic_file_sink.h"

namespace be {

    class Logger
    {
    public:
        enum Level
        {
            INFO,
            WARN,
            ERR,
            CRIT
        };

        enum Type
        {
            DEB = 1 << 0,
            CON = 1 << 1,
            TRC = 1 << 2
        };

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

    template<class... Args>
    static void Log(int level, int type, fmt::format_string<Args...> fmt, Args&&... args)
    {
        if (type & Logger::DEB)
        {
            switch (level)
            {
            case Logger::INFO: Logger::Debug()->info(fmt, std::forward<Args>(args)...); break;
            case Logger::WARN: Logger::Debug()->warn(fmt, std::forward<Args>(args)...); break;
            case Logger::ERR: Logger::Debug()->error(fmt, std::forward<Args>(args)...); break;
            case Logger::CRIT: Logger::Debug()->critical(fmt, std::forward<Args>(args)...); break;
            }
        }
        if (type & Logger::CON)
        {
            switch (level)
            {
            case Logger::INFO: Logger::Console()->info(fmt, std::forward<Args>(args)...); break;
            case Logger::WARN: Logger::Console()->warn(fmt, std::forward<Args>(args)...); break;
            case Logger::ERR: Logger::Console()->error(fmt, std::forward<Args>(args)...); break;
            case Logger::CRIT: Logger::Console()->critical(fmt, std::forward<Args>(args)...); break;
            }
        }

        if (type & Logger::TRC)
        {
            switch (level)
            {
            case Logger::INFO: Logger::Trace()->info(fmt, std::forward<Args>(args)...); break;
            case Logger::WARN: Logger::Trace()->warn(fmt, std::forward<Args>(args)...); break;
            case Logger::ERR: Logger::Trace()->error(fmt, std::forward<Args>(args)...); break;
            case Logger::CRIT: Logger::Trace()->critical(fmt, std::forward<Args>(args)...); break;
            }
        }
    }
}

//#if defined(NDEBUG) || defined(_NDEBUG) 
//	#define BE_CON_LOGINFO(...)       
//	#define BE_CON_LOGWARN(...)       
//	#define BE_CON_LOGERROR(...)      
//	#define BE_CON_LOGCRITICAL(...)   
//
//	#define BE_TRACE_LOGINFO(...)     
//	#define BE_TRACE_LOGWARN(...)     
//	#define BE_TRACE_LOGERROR(...)    
//	#define BE_TRACE_LOGCRITICAL(...) 
//
//	#define BE_DEBUG_LOGINFO(...)     
//	#define BE_DEBUG_LOGWARN(...)     
//	#define BE_DEBUG_LOGERROR(...)    
//	#define BE_DEBUG_LOGCRITICAL(...) 
//#else
//	#define BE_CON_LOGINFO(...)       SPDLOG_LOGGER_INFO(be::Logger::Console(), __VA_ARGS__)
//	#define BE_CON_LOGWARN(...)       SPDLOG_LOGGER_WARN(be::Logger::Console(), __VA_ARGS__)
//	#define BE_CON_LOGERROR(...)      SPDLOG_LOGGER_ERROR(be::Logger::Console(), __VA_ARGS__)
//	#define BE_CON_LOGCRITICAL(...)   SPDLOG_LOGGER_CRITICAL(be::Logger::Console(), __VA_ARGS__)
//
//	#define BE_TRACE_LOGINFO(...)     SPDLOG_LOGGER_INFO(be::Logger::Trace(), __VA_ARGS__)
//	#define BE_TRACE_LOGWARN(...)     SPDLOG_LOGGER_WARN(be::Logger::Trace(), __VA_ARGS__)
//	#define BE_TRACE_LOGERROR(...)    SPDLOG_LOGGER_ERROR(be::Logger::Trace(), __VA_ARGS__)
//	#define BE_TRACE_LOGCRITICAL(...) SPDLOG_LOGGER_CRITICAL(be::Logger::Trace(), __VA_ARGS__)
//
//	#define BE_DEBUG_LOGINFO(...)     SPDLOG_LOGGER_INFO(be::Logger::Debug(), __VA_ARGS__)
//	#define BE_DEBUG_LOGWARN(...)     SPDLOG_LOGGER_WARN(be::Logger::Debug(), __VA_ARGS__)
//	#define BE_DEBUG_LOGERROR(...)    SPDLOG_LOGGER_ERROR(be::Logger::Debug(), __VA_ARGS__)
//	#define BE_DEBUG_LOGCRITICAL(...) SPDLOG_LOGGER_CRITICAL(be::Logger::Debug(), __VA_ARGS__)
//#endif

namespace be {

	
}



