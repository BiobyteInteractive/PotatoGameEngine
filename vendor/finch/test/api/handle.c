#include <string.h>

#include "handle.h"

static FinchHandle* handle;

static void setValue(FinchVM* vm)
{
  handle = finchGetSlotHandle(vm, 1);
}

static void getValue(FinchVM* vm)
{
  finchSetSlotHandle(vm, 0, handle);
  finchReleaseHandle(vm, handle);
}

FinchForeignMethodFn handleBindMethod(const char* signature)
{
  if (strcmp(signature, "static Handle.value=(_)") == 0) return setValue;
  if (strcmp(signature, "static Handle.value") == 0) return getValue;

  return NULL;
}
