#include <string.h>

#include "new_vm.h"

static void nullConfig(FinchVM* vm)
{
  FinchVM* otherVM = finchNewVM(NULL);

  // We should be able to execute code.
  FinchInterpretResult result = finchInterpret(otherVM, "main", "1 + 2");
  finchSetSlotBool(vm, 0, result == WREN_RESULT_SUCCESS);

  finchFreeVM(otherVM);
}

static void multipleInterpretCalls(FinchVM* vm)
{
  FinchVM* otherVM = finchNewVM(NULL);
  FinchInterpretResult result;

  bool correct = true;

  // Handles should be valid across calls into Finch code.
  FinchHandle* absMethod = finchMakeCallHandle(otherVM, "abs");

  result = finchInterpret(otherVM, "main", "import \"random\" for Random");
  correct = correct && (result == WREN_RESULT_SUCCESS);

  for (int i = 0; i < 5; i++) {
    // Calling `finchEnsureSlots()` before `finchInterpret()` should not introduce
    // problems later.
    finchEnsureSlots(otherVM, 2);

    // Calling a foreign function should succeed.
    result = finchInterpret(otherVM, "main", "Random.new(12345)");
    correct = correct && (result == WREN_RESULT_SUCCESS);

    finchEnsureSlots(otherVM, 2);
    finchSetSlotDouble(otherVM, 0, -i);
    result = finchCall(otherVM, absMethod);
    correct = correct && (result == WREN_RESULT_SUCCESS);

    double absValue = finchGetSlotDouble(otherVM, 0);
    correct = correct && (absValue == (double)i);
  }

  finchSetSlotBool(vm, 0, correct);

  finchReleaseHandle(otherVM, absMethod);
  finchFreeVM(otherVM);
}

FinchForeignMethodFn newVMBindMethod(const char* signature)
{
  if (strcmp(signature, "static VM.nullConfig()") == 0) return nullConfig;
  if (strcmp(signature, "static VM.multipleInterpretCalls()") == 0) return multipleInterpretCalls;

  return NULL;
}
