#pragma once

#include <fstream>

template <typename T>
void LogLineAppend(const T &line)
{
    std::ofstream logfile("GAME/Log/log.txt", std::ios::app);
    logfile << line << std::endl;
    logfile.close();
}