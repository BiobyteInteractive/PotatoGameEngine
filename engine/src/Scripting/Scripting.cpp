#include "Scripting.h"
#include <string>

#include <wren.hpp>

void errorFn(WrenVM* vm, WrenErrorType errorType, const char* module, const int line, const char* msg) {
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

Scripting::Scripting() {
    wrenInitConfiguration(&this->config);

    this->config.errorFn = &errorFn;

    this->vm = wrenNewVM(&this->config);
}

Scripting::~Scripting() {
    wrenFreeVM(this->vm);
}

WrenInterpretResult Scripting::Interpret(std::string package, std::string script) {
    return wrenInterpret(this->vm, package.c_str(), script.c_str());
}