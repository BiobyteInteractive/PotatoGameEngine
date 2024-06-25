#pragma once
#ifndef SCRIPTING_H
#define SCRIPTING_H

#define DllExport __declspec( dllexport )

#include <string>

#include <wren.hpp>

class DllExport Scripting {
    public:
        static Scripting& GetInstance() {
            static Scripting instance;
            return instance;
        }

        Scripting(const Scripting&) = delete;
        Scripting& operator=(const Scripting&) = delete;

        WrenInterpretResult Interpret(std::string package, std::string script);
        void RegisterClass();
    private:
        Scripting();
        ~Scripting();
        friend void errorFn(WrenVM* vm, WrenErrorType errorType, const char* module, const int line, const char* msg);
    private:
        WrenConfiguration config;
        WrenVM* vm;
};

#endif