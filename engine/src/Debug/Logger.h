#pragma once

#define DllExport __declspec( dllexport )

#include <fstream>
#include <string>

namespace Engine {
    class DllExport Logger {
        public:
            static Logger& GetInstance() {
                static Logger instance;
                return instance;
            }

            Logger(const Logger&) = delete;
            Logger& operator=(const Logger&) = delete;

            void Error(const std::string message);
            void Debug(const std::string message);
            void Info(const std::string message);
        private:

            Logger();
            ~Logger();
            void Log(const std::string message, const std::string mode);
        public:
            std::ofstream m_OutputStream;
    };
}