#include "finch.h"

FinchForeignMethodFn foreignClassBindMethod(const char* signature);
void foreignClassBindClass(
    const char* className, FinchForeignClassMethods* methods);
