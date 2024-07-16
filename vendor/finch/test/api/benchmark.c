#include <string.h>
#include <time.h>

#include "benchmark.h"

static void arguments(FinchVM* vm)
{
  double result = 0;

  result += finchGetSlotDouble(vm, 1);
  result += finchGetSlotDouble(vm, 2);
  result += finchGetSlotDouble(vm, 3);
  result += finchGetSlotDouble(vm, 4);

  finchSetSlotDouble(vm, 0, result);
}

const char* testScript =
"class Test {\n"
"  static method(a, b, c, d) { a + b + c + d }\n"
"}\n";

static void call(FinchVM* vm)
{
  int iterations = (int)finchGetSlotDouble(vm, 1);

  // Since the VM is not re-entrant, we can't call from within this foreign
  // method. Instead, make a new VM to run the call test in.
  FinchConfiguration config;
  finchInitConfiguration(&config);
  FinchVM* otherVM = finchNewVM(&config);

  finchInterpret(otherVM, "main", testScript);

  FinchHandle* method = finchMakeCallHandle(otherVM, "method(_,_,_,_)");

  finchEnsureSlots(otherVM, 1);
  finchGetVariable(otherVM, "main", "Test", 0);
  FinchHandle* testClass = finchGetSlotHandle(otherVM, 0);

  double startTime = (double)clock() / CLOCKS_PER_SEC;

  double result = 0;
  for (int i = 0; i < iterations; i++)
  {
    finchEnsureSlots(otherVM, 5);
    finchSetSlotHandle(otherVM, 0, testClass);
    finchSetSlotDouble(otherVM, 1, 1.0);
    finchSetSlotDouble(otherVM, 2, 2.0);
    finchSetSlotDouble(otherVM, 3, 3.0);
    finchSetSlotDouble(otherVM, 4, 4.0);

    finchCall(otherVM, method);

    result += finchGetSlotDouble(otherVM, 0);
  }

  double elapsed = (double)clock() / CLOCKS_PER_SEC - startTime;

  finchReleaseHandle(otherVM, testClass);
  finchReleaseHandle(otherVM, method);
  finchFreeVM(otherVM);

  if (result == (1.0 + 2.0 + 3.0 + 4.0) * iterations)
  {
    finchSetSlotDouble(vm, 0, elapsed);
  }
  else
  {
    // Got the wrong result.
    finchSetSlotBool(vm, 0, false);
  }
}

FinchForeignMethodFn benchmarkBindMethod(const char* signature)
{
  if (strcmp(signature, "static Benchmark.arguments(_,_,_,_)") == 0) return arguments;
  if (strcmp(signature, "static Benchmark.call(_)") == 0) return call;

  return NULL;
}
