#include "finch.h"

FinchForeignMethodFn mapsBindMethod(const char* signature);
void mapBindClass(
    const char* className, FinchForeignClassMethods* methods);
