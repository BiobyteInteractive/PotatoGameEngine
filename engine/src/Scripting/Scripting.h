#pragma once

#ifndef DllExport
#ifdef DLLBuild
#define DllExport __declspec( dllexport )
#else
#define DllExport __declspec( dllimport )
#endif
#endif

#include <string>
#include <finch.hpp>

namespace Engine {
    class DllExport Scripting {
        public:
            static Scripting& GetInstance() {
                static Scripting instance;
                return instance;
            }

            Scripting(const Scripting&) = delete;
            Scripting& operator=(const Scripting&) = delete;

            FinchInterpretResult Interpret(std::string package, std::string script);
        private:
            Scripting();
            ~Scripting();
            friend void errorFn(FinchVM* vm, FinchErrorType errorType, const char* module, const int line, const char* msg);
            friend void writeFn(FinchVM* vm, const char* text);
            friend FinchForeignClassMethods bindForeignClass(FinchVM* vm, const char* module, const char* className, const char* superClassName);
        private:
            FinchConfiguration config;
            FinchVM* vm;
    };
}