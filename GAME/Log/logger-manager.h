#pragma once

#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <source_location>
#include <filesystem>

inline const std::string& LogFilename()
{
    // Shared by all LogLineAppend calls, regardless of the message type.
    static const std::string filename = []() -> std::string
    {
        std::time_t now = std::time(nullptr);
        std::tm* localtime = std::localtime(&now);

        if (!localtime)
            return "GAME/Log/log.txt";

        std::ostringstream oss;
        oss << "GAME/Log/game_log_" << std::put_time(localtime, "%Y-%m-%d_%H-%M-%S") << ".txt";
        return oss.str();
    }();

    return filename;
}

template <typename T>
void LogLineAppend(const T &line, std::source_location location = std::source_location::current())
{
    std::ofstream logfile(LogFilename(), std::ios::app);
    logfile << "File: " << std::filesystem::path(location.file_name()).filename() << " Line: " << location.line() << " Info: " << line << std::endl;
}
