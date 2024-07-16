#ifndef finch_debug_h
#define finch_debug_h

#include "finch_value.h"
#include "finch_vm.h"

// Prints the stack trace for the current fiber.
//
// Used when a fiber throws a runtime error which is not caught.
void finchDebugPrintStackTrace(FinchVM* vm);

// The "dump" functions are used for debugging Finch itself. Normal code paths
// will not call them unless one of the various DEBUG_ flags is enabled.

// Prints a representation of [value] to stdout.
void finchDumpValue(Value value);

// Prints a representation of the bytecode for [fn] at instruction [i].
int finchDumpInstruction(FinchVM* vm, ObjFn* fn, int i);

// Prints the disassembled code for [fn] to stdout.
void finchDumpCode(FinchVM* vm, ObjFn* fn);

// Prints the contents of the current stack for [fiber] to stdout.
void finchDumpStack(ObjFiber* fiber);

#endif
