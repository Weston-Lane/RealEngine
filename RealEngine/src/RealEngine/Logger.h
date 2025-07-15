#pragma once
#include "pch.h"

/* Disable and enable log levels via cmake compile definitions
* This macro based feature toggle is useful since all of the stray Debug 
* and Trace calls won't be compiled with the program 
* 
* Call with RL_<levelname> ex: RL_DEBUG("[{},{}]", vec2.x,vec2.y) */

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1
#define GL_LOG_ENABLED 1

#ifdef RELEASE
    #if RELEASE==1
        #define LOG_DEBUG_ENABLED 0
        #define LOG_TRACE_ENABLED 0
    #endif
#endif

namespace Real
{
    class Log
    {
    public:
        typedef enum LogLevel
        {
            LOG_LEVEL_FATAL = 0,
            LOG_LEVEL_ERROR = 1,
            LOG_LEVEL_WARN = 2,
            LOG_LEVEL_INFO = 3,
            LOG_LEVEL_DEBUG = 4,
            LOG_LEVEL_TRACE = 5,
        }LogLevel;

        /// <summary>
        /// Formating similar to C# format strings
        /// Call with RL_<levelname> ex: RL_DEBUG("[{},{}]", vec2.x,vec2.y)
        /// </summary>
        /// <typeparam name="...Args"></typeparam>
        /// <param name="level"></param>
        /// <param name="coreLog"></param>
        /// <param name="fmt"></param>
        /// <param name="...args"></param>
        template<typename... Args>
        static void log_output(LogLevel level, bool coreLog, std::format_string<Args...> fmt, Args&&... args)
        {
            std::string levelStrings[6] = { "FATAL 💀:", "ERROR 😵:", "WARN ⚠️:",
                             "INFO ℹ️:", "DEBUG 🐛:", "TRACE:" };
            
            SetConsoleOutputCP(CP_UTF8);
            
            HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);

            //save prv attribute so I can get the prv settings back
            CONSOLE_SCREEN_BUFFER_INFO ci;
            GetConsoleScreenBufferInfo(cHandle, &ci);
            WORD originalAttrib = ci.wAttributes;

            //different cases for string headers
            if(coreLog)//sets background for beginning of string if using coreLog
            { 
                UINT8 color[6] = { 
                    FOREGROUND_RED | BACKGROUND_INTENSITY,//FATAL
                    FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY,//ERROR
                    FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_INTENSITY,//WARN
                    FOREGROUND_GREEN | BACKGROUND_INTENSITY,//INFO
                    FOREGROUND_RED | FOREGROUND_BLUE | BACKGROUND_INTENSITY ,//DEBUG
                    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY//TRACE 
                };
                SetConsoleTextAttribute(cHandle, color[level]);
                std::print("REAL Core "); std::print("{}", levelStrings[level]);
            }
            else//same colors but with no background
            {
                UINT8 color[6] = {
                    FOREGROUND_RED | FOREGROUND_INTENSITY,//FATAL
                    FOREGROUND_RED,//ERROR
                    FOREGROUND_RED | FOREGROUND_GREEN,//WARN
                    FOREGROUND_GREEN,//INFO
                    FOREGROUND_RED | FOREGROUND_BLUE,//DEBUG
                    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY//TRACE 
                };
                SetConsoleTextAttribute(cHandle, color[level]);
                std::print("{}", levelStrings[level]);
            }
            //for rest of string
            UINT8 color[6] = {
                    FOREGROUND_RED | FOREGROUND_INTENSITY,//FATAL
                    FOREGROUND_RED,//ERROR
                    FOREGROUND_RED | FOREGROUND_GREEN,//WARN
                    FOREGROUND_GREEN,//INFO
                    FOREGROUND_RED | FOREGROUND_BLUE,//DEBUG
                    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY//TRACE 
            };
            SetConsoleTextAttribute(cHandle, color[level]);
            std::println(fmt, std::forward<Args>(args)...);

            //reset to original settings
            SetConsoleTextAttribute(cHandle, originalAttrib);
        }
    };
}

//------------------------Logger Defines Used For Calling----------------------------//
#define RL_CORE_FATAL(...) Real::Log::log_output(Real::Log::LOG_LEVEL_FATAL,true, __VA_ARGS__);//always compiled
#define RL_CORE_ERROR(...) Real::Log::log_output(Real::Log::LOG_LEVEL_ERROR,true,__VA_ARGS__);//always compiled
#define RL_FATAL(...) Real::Log::log_output(Real::Log::LOG_LEVEL_FATAL,false, __VA_ARGS__);//always compiled
#define RL_ERROR(...) Real::Log::log_output(Real::Log::LOG_LEVEL_ERROR,false,__VA_ARGS__);//always compiled

#if LOG_WARN_ENABLED==1
    #define RL_CORE_WARN(...) Real::Log::log_output(Real::Log::LOG_LEVEL_WARN,true, __VA_ARGS__);
    #define RL_WARN(...) Real::Log::log_output(Real::Log::LOG_LEVEL_WARN,false, __VA_ARGS__);
#else
    #define RL_WARN(...)
#endif
#if LOG_INFO_ENABLED==1
    #define RL_CORE_INFO(...) Real::Log::log_output(Real::Log::LOG_LEVEL_INFO,true, __VA_ARGS__);
    #define RL_INFO(...) Real::Log::log_output(Real::Log::LOG_LEVEL_INFO,false, __VA_ARGS__);
#else
    #define RL_INFO(...)
#endif
#if LOG_DEBUG_ENABLED==1
    #define RL_CORE_DEBUG(...) Real::Log::log_output(Real::Log::LOG_LEVEL_DEBUG,true, __VA_ARGS__);
    #define RL_DEBUG(...) Real::Log::log_output(Real::Log::LOG_LEVEL_DEBUG,false, __VA_ARGS__);
#else
    #define RL_DEBUG(...)
#endif
#if LOG_TRACE_ENABLED==1
    #define RL_CORE_TRACE(...) Real::Log::log_output(Real::Log::LOG_LEVEL_TRACE,true, __VA_ARGS__);
    #define RL_TRACE(...) Real::Log::log_output(Real::Log::LOG_LEVEL_TRACE,false, __VA_ARGS__);
#else
    #define RL_TRACE(...)
#endif



