#include <stdio.h>
#include <string.h>

#include "finch.h"

static void counterAllocate(FinchVM* vm)
{
  double* counter = (double*)finchSetSlotNewForeign(vm, 0, 0, sizeof(double));
  *counter = finchGetSlotDouble(vm, 1);
}

void resetStackAfterForeignConstructBindClass(
    const char* className, FinchForeignClassMethods* methods)
{
  if (strcmp(className, "ResetStackForeign") == 0)
  {
    methods->allocate = counterAllocate;
    return;
  }
}

int resetStackAfterForeignConstructRunTests(FinchVM* vm)
{
  finchEnsureSlots(vm, 1);
  finchGetVariable(vm,
      "./test/api/reset_stack_after_foreign_construct", "Test", 0);
  FinchHandle* testClass = finchGetSlotHandle(vm, 0);

  FinchHandle* callConstruct = finchMakeCallHandle(vm, "callConstruct()");
  FinchHandle* afterConstruct = finchMakeCallHandle(vm, "afterConstruct(_,_)");

  finchEnsureSlots(vm, 1);
  finchSetSlotHandle(vm, 0, testClass);
  finchCall(vm, callConstruct);

  finchEnsureSlots(vm, 3);
  finchSetSlotHandle(vm, 0, testClass);
  finchSetSlotDouble(vm, 1, 1.0);
  finchSetSlotDouble(vm, 2, 2.0);
  finchCall(vm, afterConstruct);

  finchReleaseHandle(vm, testClass);
  finchReleaseHandle(vm, callConstruct);
  finchReleaseHandle(vm, afterConstruct);

  return 0;
}
