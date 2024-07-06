#include "Scripting.h"

#include <finch.hpp>

#include <iostream>
#include <string>

namespace Engine {
    void errorFn(FinchVM* vm, FinchErrorType errorType, const char* module, const int line, const char* msg) {
        switch (errorType)
        {
            case WREN_ERROR_COMPILE:
                {
                printf("[%s line %d] [Error] %s\n", module, line, msg);
                } break;
            case WREN_ERROR_STACK_TRACE:
                {
                printf("[%s line %d] in %s\n", module, line, msg);
                } break;
            case WREN_ERROR_RUNTIME:
                {
                printf("[Runtime Error] %s\n", msg);
                } break;
        }
    }

    void writeFn(FinchVM* vm, const char* text)
    {
        std::cout << text;
    }

    FinchForeignClassMethods bindForeignClass(FinchVM* vm, const char* module, const char* className, const char* superClassName) {
        FinchForeignClassMethods methods;

        std::cout << "Module: " << module << std::endl;
        std::cout << "Class: " << className << std::endl;
        std::cout << "Super Class: " << superClassName << std::endl;

        // Unknown class.
        methods.allocate = NULL;
        methods.finalize = NULL;

        return methods;
    }

    Scripting::Scripting() {
        finchInitConfiguration(&this->config);

        this->config.errorFn = &errorFn;
        this->config.writeFn = &writeFn;
        this->config.bindForeignClassFn = bindForeignClass;

        this->vm = finchNewVM(&this->config);
    }

    Scripting::~Scripting() {
        finchFreeVM(this->vm);
    }

    FinchInterpretResult Scripting::Interpret(std::string package, std::string script) {
        return finchInterpret(this->vm, package.c_str(), script.c_str());
    }
}