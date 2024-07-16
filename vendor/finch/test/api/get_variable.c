#include <string.h>

#include "get_variable.h"

static void beforeDefined(FinchVM* vm)
{
  finchGetVariable(vm, "./test/api/get_variable", "A", 0);
}

static void afterDefined(FinchVM* vm)
{
  finchGetVariable(vm, "./test/api/get_variable", "A", 0);
}

static void afterAssigned(FinchVM* vm)
{
  finchGetVariable(vm, "./test/api/get_variable", "A", 0);
}

static void otherSlot(FinchVM* vm)
{
  finchEnsureSlots(vm, 3);
  finchGetVariable(vm, "./test/api/get_variable", "B", 2);

  // Move it into return position.
  const char* string = finchGetSlotString(vm, 2);
  finchSetSlotString(vm, 0, string);
}

static void otherModule(FinchVM* vm)
{
  finchGetVariable(vm, "./test/api/get_variable_module", "Variable", 0);
}

static void hasVariable(FinchVM* vm)
{
  const char* module = finchGetSlotString(vm, 1);
  const char* variable = finchGetSlotString(vm, 2);

  bool result = finchHasVariable(vm, module, variable);
  finchEnsureSlots(vm, 1);
  finchSetSlotBool(vm, 0, result);
}

static void hasModule(FinchVM* vm)
{
  const char* module = finchGetSlotString(vm, 1);

  bool result = finchHasModule(vm, module);
  finchEnsureSlots(vm, 1);
  finchSetSlotBool(vm, 0, result);
}

FinchForeignMethodFn getVariableBindMethod(const char* signature)
{
  if (strcmp(signature, "static GetVariable.beforeDefined()") == 0) return beforeDefined;
  if (strcmp(signature, "static GetVariable.afterDefined()") == 0) return afterDefined;
  if (strcmp(signature, "static GetVariable.afterAssigned()") == 0) return afterAssigned;
  if (strcmp(signature, "static GetVariable.otherSlot()") == 0) return otherSlot;
  if (strcmp(signature, "static GetVariable.otherModule()") == 0) return otherModule;
  
  if (strcmp(signature, "static Has.variable(_,_)") == 0) return hasVariable;
  if (strcmp(signature, "static Has.module(_)") == 0) return hasModule;

  return NULL;
}
