#pragma once

#ifndef DllExport
#ifdef DLLBuild
#define DllExport __declspec( dllexport )
#else
#define DllExport __declspec( dllimport )
#endif
#endif

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
        private:
            std::ofstream m_OutputStream;
    };
}