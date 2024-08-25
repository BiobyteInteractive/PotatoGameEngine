#include "Logger.h"

#include <chrono>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

namespace Engine {
    Logger::Logger() {
        this->m_OutputStream.open("engine.log");
    }

    Logger::~Logger() {
        this->m_OutputStream.close();
    }

    void Logger::Error(const std::string message) {
        this->Log(message, "ERROR"); 
    }

    void Logger::Debug(const std::string message) {
        this->Log(message, "DEBUG"); 
    }

    void Logger::Info(const std::string message) {
        this->Log(message, "INFO"); 
    }

    void Logger::Log(const std::string message, const std::string mode) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        struct tm now_tm;
        localtime_s(&now_tm, &now_time_t);

        std::ostringstream oss;
        oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");

        std::string log = std::format("[{}] [{}] {}", oss.str(), mode, message);

        this->m_OutputStream << log << std::endl;
        std::cout            << log << std::endl;
        this->m_OutputStream.flush(); 
    }
}