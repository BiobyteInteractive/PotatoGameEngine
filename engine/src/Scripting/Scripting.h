#pragma once
#ifndef SCRIPTING_H
#define SCRIPTING_H

#define DllExport __declspec( dllexport )

#include <string>

#include <wren.hpp>

class DllExport Scripting {
    public:
        Scripting();
        ~Scripting();

        WrenInterpretResult Interpret(std::string package, std::string script);
        void RegisterClass();
    private:
        friend void errorFn(WrenVM* vm, WrenErrorType errorType, const char* module, const int line, const char* msg);
    private:
        WrenConfiguration config;
        WrenVM* vm;
};

#endif