#include <string.h>

#include "user_data.h"

static const char* data = "my user data";
static const char* otherData = "other user data";

void* testReallocateFn(void* ptr, size_t newSize, void* userData) {
  if (strcmp(userData, data) != 0) return NULL;

  if (newSize == 0)
  {
    free(ptr);
    return NULL;
  }

  return realloc(ptr, newSize);
}

static void test(FinchVM* vm)
{
  FinchConfiguration configuration;
  finchInitConfiguration(&configuration);

  // Should default to NULL.
  if (configuration.userData != NULL)
  {
    finchSetSlotBool(vm, 0, false);
    return;
  }

  configuration.reallocateFn = testReallocateFn;
  configuration.userData = (void*)data;

  FinchVM* otherVM = finchNewVM(&configuration);

  // Should be able to get it.
  if (finchGetUserData(otherVM) != data)
  {
    finchSetSlotBool(vm, 0, false);
    finchFreeVM(otherVM);
    return;
  }

  // Should be able to set it.
  finchSetUserData(otherVM, (void*)otherData);

  if (finchGetUserData(otherVM) != otherData)
  {
    finchSetSlotBool(vm, 0, false);
    finchFreeVM(otherVM);
    return;
  }

  finchSetSlotBool(vm, 0, true);
  finchFreeVM(otherVM);
}

FinchForeignMethodFn userDataBindMethod(const char* signature)
{
  if (strcmp(signature, "static UserData.test") == 0) return test;

  return NULL;
}
