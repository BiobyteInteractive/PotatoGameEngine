#ifndef finch_opt_random_h
#define finch_opt_random_h

#include "finch_common.h"
#include "finch.h"

#if WREN_OPT_RANDOM

const char* finchRandomSource();
FinchForeignClassMethods finchRandomBindForeignClass(FinchVM* vm,
                                                   const char* module,
                                                   const char* className);
FinchForeignMethodFn finchRandomBindForeignMethod(FinchVM* vm,
                                                const char* className,
                                                bool isStatic,
                                                const char* signature);

#endif

#endif
