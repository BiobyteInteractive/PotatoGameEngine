#include <stdio.h>
#include <string.h>

#include "error.h"

static void runtimeError(FinchVM* vm)
{
  finchEnsureSlots(vm, 1);
  finchSetSlotString(vm, 0, "Error!");
  finchAbortFiber(vm, 0);
}

FinchForeignMethodFn errorBindMethod(const char* signature)
{
  if (strcmp(signature, "static Error.runtimeError") == 0) return runtimeError;

  return NULL;
}
