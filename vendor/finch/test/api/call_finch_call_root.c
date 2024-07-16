#include <stdio.h>
#include <string.h>

#include "finch.h"
#include "../test.h"

int callFinchCallRootRunTests(FinchVM* vm)
{
  int exitCode = 0;
  finchEnsureSlots(vm, 1);
  finchGetVariable(vm, "./test/api/call_finch_call_root", "Test", 0);
  FinchHandle* testClass = finchGetSlotHandle(vm, 0);

  FinchHandle* run = finchMakeCallHandle(vm, "run()");

  finchEnsureSlots(vm, 1);
  finchSetSlotHandle(vm, 0, testClass);
  FinchInterpretResult result = finchCall(vm, run);
  if (result == WREN_RESULT_RUNTIME_ERROR)
  {
    exitCode = WREN_EX_SOFTWARE;
  }
  else
  {
    printf("Missing runtime error.\n");
  }

  finchReleaseHandle(vm, testClass);
  finchReleaseHandle(vm, run);
  return exitCode;
}
