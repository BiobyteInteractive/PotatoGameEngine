#include <stdio.h>
#include <string.h>

#include "finch.h"

int resetStackAfterCallAbortRunTests(FinchVM* vm)
{
  finchEnsureSlots(vm, 1);
  finchGetVariable(vm, "./test/api/reset_stack_after_call_abort", "Test", 0);
  FinchHandle* testClass = finchGetSlotHandle(vm, 0);

  FinchHandle* abortFiber = finchMakeCallHandle(vm, "abortFiber()");
  FinchHandle* afterAbort = finchMakeCallHandle(vm, "afterAbort(_,_)");

  finchEnsureSlots(vm, 1);
  finchSetSlotHandle(vm, 0, testClass);
  finchCall(vm, abortFiber);

  finchEnsureSlots(vm, 3);
  finchSetSlotHandle(vm, 0, testClass);
  finchSetSlotDouble(vm, 1, 1.0);
  finchSetSlotDouble(vm, 2, 2.0);
  finchCall(vm, afterAbort);

  finchReleaseHandle(vm, testClass);
  finchReleaseHandle(vm, abortFiber);
  finchReleaseHandle(vm, afterAbort);
  return 0;
}
