#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#define DllExport __declspec( dllexport )

#include <string>

class DllExport Logger {
    public:
        Logger();
        ~Logger();

        void Error(const std::string message);
        void Debug(const std::string message);
        void Info(const std::string message);
};

#endif