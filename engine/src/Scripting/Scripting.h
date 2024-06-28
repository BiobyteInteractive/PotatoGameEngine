#pragma once

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
    private:
        Scripting();
        ~Scripting();
        friend void errorFn(WrenVM* vm, WrenErrorType errorType, const char* module, const int line, const char* msg);
        friend void writeFn(WrenVM* vm, const char* text);
        friend WrenForeignClassMethods bindForeignClass(WrenVM* vm, const char* module, const char* className, const char* superClassName);
    private:
        WrenConfiguration config;
        WrenVM* vm;
};