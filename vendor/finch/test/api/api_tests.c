#include "./api_tests.h"

static const char* testName = NULL;

FinchForeignMethodFn APITest_bindForeignMethod(
    FinchVM* vm, const char* module, const char* className,
    bool isStatic, const char* signature)
{
  if (strncmp(module, "./test/", 7) != 0) return NULL;

  // For convenience, concatenate all of the method qualifiers into a single
  // signature string.
  char fullName[256];
  fullName[0] = '\0';
  if (isStatic) strcat(fullName, "static ");
  strcat(fullName, className);
  strcat(fullName, ".");
  strcat(fullName, signature);

  FinchForeignMethodFn method = NULL;

  method = benchmarkBindMethod(fullName);
  if (method != NULL) return method;

  method = callCallsForeignBindMethod(fullName);
  if (method != NULL) return method;

  method = errorBindMethod(fullName);
  if (method != NULL) return method;

  method = getVariableBindMethod(fullName);
  if (method != NULL) return method;

  method = foreignClassBindMethod(fullName);
  if (method != NULL) return method;

  method = handleBindMethod(fullName);
  if (method != NULL) return method;

  method = listsBindMethod(fullName);
  if (method != NULL) return method;

  method = mapsBindMethod(fullName);
  if (method != NULL) return method;

  method = newVMBindMethod(fullName);
  if (method != NULL) return method;

  method = resolutionBindMethod(fullName);
  if (method != NULL) return method;

  method = slotsBindMethod(fullName);
  if (method != NULL) return method;

  method = userDataBindMethod(fullName);
  if (method != NULL) return method;

  fprintf(stderr,
      "Unknown foreign method '%s' for test '%s'\n", fullName, testName);
  exit(1);
  return NULL;
}

FinchForeignClassMethods APITest_bindForeignClass(
    FinchVM* vm, const char* module, const char* className)
{
  FinchForeignClassMethods methods = { NULL, NULL };
  if (strncmp(module, "./test/api", 7) != 0) return methods;

  foreignClassBindClass(className, &methods);
  if (methods.allocate != NULL) return methods;

  resetStackAfterForeignConstructBindClass(className, &methods);
  if (methods.allocate != NULL) return methods;

  slotsBindClass(className, &methods);
  if (methods.allocate != NULL) return methods;

  fprintf(stderr,
          "Unknown foreign class '%s' for test '%s'\n", className, testName);
  exit(1);
  return methods;
}

int APITest_Run(FinchVM* vm, const char* inTestName)
{
  testName = inTestName;
  if (strstr(inTestName, "/call.finch") != NULL)
  {
    return callRunTests(vm);
  }
  else if (strstr(inTestName, "/call_calls_foreign.finch") != NULL)
  {
    return callCallsForeignRunTests(vm);
  }
  else if (strstr(inTestName, "/call_finch_call_root.finch") != NULL)
  {
    return callFinchCallRootRunTests(vm);
  }
  else if (strstr(inTestName, "/reset_stack_after_call_abort.finch") != NULL)
  {
    return resetStackAfterCallAbortRunTests(vm);
  }
  else if (strstr(inTestName, "/reset_stack_after_foreign_construct.finch") != NULL)
  {
    return resetStackAfterForeignConstructRunTests(vm);
  }

  return 0;
}
