#include <stdio.h>
#include <string.h>

#include "finch.h"

static void api(FinchVM *vm) {
  // Grow the slot array. This should trigger the stack to be moved.
  finchEnsureSlots(vm, 10);
  finchSetSlotNewList(vm, 0);

  for (int i = 1; i < 10; i++)
  {
    finchSetSlotDouble(vm, i, i);
    finchInsertInList(vm, 0, -1, i);
  }
}

FinchForeignMethodFn callCallsForeignBindMethod(const char* signature)
{
  if (strcmp(signature, "static CallCallsForeign.api()") == 0) return api;

  return NULL;
}

int callCallsForeignRunTests(FinchVM* vm)
{
  finchEnsureSlots(vm, 1);
  finchGetVariable(vm, "./test/api/call_calls_foreign", "CallCallsForeign", 0);
  FinchHandle* apiClass = finchGetSlotHandle(vm, 0);
  FinchHandle *call = finchMakeCallHandle(vm, "call(_)");

  finchEnsureSlots(vm, 2);
  finchSetSlotHandle(vm, 0, apiClass);
  finchSetSlotString(vm, 1, "parameter");

  printf("slots before %d\n", finchGetSlotCount(vm));
  finchCall(vm, call);

  // We should have a single slot count for the return.
  printf("slots after %d\n", finchGetSlotCount(vm));

  finchReleaseHandle(vm, call);
  finchReleaseHandle(vm, apiClass);
  return 0;
}
