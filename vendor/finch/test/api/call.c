#include <stdio.h>
#include <string.h>

#include "call.h"

int callRunTests(FinchVM* vm)
{
  finchEnsureSlots(vm, 1);
  finchGetVariable(vm, "./test/api/call", "Call", 0);
  FinchHandle* callClass = finchGetSlotHandle(vm, 0);

  FinchHandle* noParams = finchMakeCallHandle(vm, "noParams");
  FinchHandle* zero = finchMakeCallHandle(vm, "zero()");
  FinchHandle* one = finchMakeCallHandle(vm, "one(_)");
  FinchHandle* two = finchMakeCallHandle(vm, "two(_,_)");
  FinchHandle* unary = finchMakeCallHandle(vm, "-");
  FinchHandle* binary = finchMakeCallHandle(vm, "-(_)");
  FinchHandle* subscript = finchMakeCallHandle(vm, "[_,_]");
  FinchHandle* subscriptSet = finchMakeCallHandle(vm, "[_,_]=(_)");

  // Different arity.
  finchEnsureSlots(vm, 1);
  finchSetSlotHandle(vm, 0, callClass);
  finchCall(vm, noParams);

  finchEnsureSlots(vm, 1);
  finchSetSlotHandle(vm, 0, callClass);
  finchCall(vm, zero);

  finchEnsureSlots(vm, 2);
  finchSetSlotHandle(vm, 0, callClass);
  finchSetSlotDouble(vm, 1, 1.0);
  finchCall(vm, one);

  finchEnsureSlots(vm, 3);
  finchSetSlotHandle(vm, 0, callClass);
  finchSetSlotDouble(vm, 1, 1.0);
  finchSetSlotDouble(vm, 2, 2.0);
  finchCall(vm, two);

  // Operators.
  finchEnsureSlots(vm, 1);
  finchSetSlotHandle(vm, 0, callClass);
  finchCall(vm, unary);

  finchEnsureSlots(vm, 2);
  finchSetSlotHandle(vm, 0, callClass);
  finchSetSlotDouble(vm, 1, 1.0);
  finchCall(vm, binary);

  finchEnsureSlots(vm, 3);
  finchSetSlotHandle(vm, 0, callClass);
  finchSetSlotDouble(vm, 1, 1.0);
  finchSetSlotDouble(vm, 2, 2.0);
  finchCall(vm, subscript);

  finchEnsureSlots(vm, 4);
  finchSetSlotHandle(vm, 0, callClass);
  finchSetSlotDouble(vm, 1, 1.0);
  finchSetSlotDouble(vm, 2, 2.0);
  finchSetSlotDouble(vm, 3, 3.0);
  finchCall(vm, subscriptSet);

  // Returning a value.
  FinchHandle* getValue = finchMakeCallHandle(vm, "getValue()");
  finchEnsureSlots(vm, 1);
  finchSetSlotHandle(vm, 0, callClass);
  finchCall(vm, getValue);
  printf("slots after call: %d\n", finchGetSlotCount(vm));
  FinchHandle* value = finchGetSlotHandle(vm, 0);

  // Different argument types.
  finchEnsureSlots(vm, 3);
  finchSetSlotHandle(vm, 0, callClass);
  finchSetSlotBool(vm, 1, true);
  finchSetSlotBool(vm, 2, false);
  finchCall(vm, two);

  finchEnsureSlots(vm, 3);
  finchSetSlotHandle(vm, 0, callClass);
  finchSetSlotDouble(vm, 1, 1.2);
  finchSetSlotDouble(vm, 2, 3.4);
  finchCall(vm, two);

  finchEnsureSlots(vm, 3);
  finchSetSlotHandle(vm, 0, callClass);
  finchSetSlotString(vm, 1, "string");
  finchSetSlotString(vm, 2, "another");
  finchCall(vm, two);

  finchEnsureSlots(vm, 3);
  finchSetSlotHandle(vm, 0, callClass);
  finchSetSlotNull(vm, 1);
  finchSetSlotHandle(vm, 2, value);
  finchCall(vm, two);

  // Truncate a string, or allow null bytes.
  finchEnsureSlots(vm, 3);
  finchSetSlotHandle(vm, 0, callClass);
  finchSetSlotBytes(vm, 1, "string", 3);
  finchSetSlotBytes(vm, 2, "b\0y\0t\0e", 7);
  finchCall(vm, two);

  // Call ignores with extra temporary slots on stack.
  finchEnsureSlots(vm, 10);
  finchSetSlotHandle(vm, 0, callClass);
  for (int i = 1; i < 10; i++)
  {
    finchSetSlotDouble(vm, i, i * 0.1);
  }
  finchCall(vm, one);

  finchReleaseHandle(vm, callClass);
  finchReleaseHandle(vm, noParams);
  finchReleaseHandle(vm, zero);
  finchReleaseHandle(vm, one);
  finchReleaseHandle(vm, two);
  finchReleaseHandle(vm, getValue);
  finchReleaseHandle(vm, value);
  finchReleaseHandle(vm, unary);
  finchReleaseHandle(vm, binary);
  finchReleaseHandle(vm, subscript);
  finchReleaseHandle(vm, subscriptSet);

  return 0;
}
