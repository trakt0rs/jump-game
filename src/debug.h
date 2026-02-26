#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include <format>
#include <stdexcept>
#include <string_view>


static void SDLCheckError(const char* function, const char* file, int line) {
    const char* error = SDL_GetError();
    if (error && *error != '\0') {
        std::cerr << "[SDL Error] " << function 
                  << " " << error 
                  << " " << file << ":" << line << std::endl;
        SDL_ClearError();
    }
}

// For void functions
#define SDL_CALL_VOID(x)                    \
    x;                                      \
    SDLCheckError(#x, __FILE__, __LINE__)

// For functions that return a value
#define SDL_CALL(x)                             \
    [&]() {                                     \
        auto _r = (x);                          \
        SDLCheckError(#x, __FILE__, __LINE__);  \
        return _r;                              \
    }()


namespace LOG
{
namespace __detail
{
    inline void Print(const char* level, const char* file, int line, const char* func, const std::string& msg, bool fatal=false)
    {
        std::ostream& out = (level == std::string("INFO")) ? std::cout : std::cerr;
        out << "[" << level << "] " << file << ":" << line << " (" << func << ") | " << msg << "\n";
        if(fatal) throw std::runtime_error(msg);
    }
}

template<typename... Args>
inline void Info(const char* file, int line, const char* func, const char* fmt, Args&&... args)
{
    __detail::Print("INFO", file, line, func, std::vformat(fmt, std::make_format_args(args...)));
}

template<typename... Args>
inline void Warn(const char* file, int line, const char* func, const char* fmt, Args&&... args)
{
    __detail::Print("WARN", file, line, func, std::vformat(fmt, std::make_format_args(args...)));
}

template<typename... Args>
inline void Error(const char* file, int line, const char* func, const char* fmt, Args&&... args)
{
    __detail::Print("ERROR", file, line, func, std::vformat(fmt, std::make_format_args(args...)));
}

template<typename... Args>
inline void Fatal(const char* file, int line, const char* func, const char* fmt, Args&&... args)
{
    __detail::Print("FATAL", file, line, func, std::vformat(fmt, std::make_format_args(args...)), true);
}

// ------------------ Macros for automatic file/line/function ------------------

#define LOG_INFO(fmt, ...)  LOG::Info(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  LOG::Warn(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) LOG::Error(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...) LOG::Fatal(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

}