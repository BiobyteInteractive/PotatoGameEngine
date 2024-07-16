#ifndef finch_opt_meta_h
#define finch_opt_meta_h

#include "finch_common.h"
#include "finch.h"

// This module defines the Meta class and its associated methods.
#if WREN_OPT_META

const char* finchMetaSource();
FinchForeignMethodFn finchMetaBindForeignMethod(FinchVM* vm,
                                              const char* className,
                                              bool isStatic,
                                              const char* signature);

#endif

#endif
