#include <stdio.h>
#include <string.h>

#include "resolution.h"

static void writeFn(FinchVM* vm, const char* text)
{
  printf("%s", text);
}

static void reportError(FinchVM* vm, FinchErrorType type,
                        const char* module, int line, const char* message)
{
  if (type == WREN_ERROR_RUNTIME) printf("%s\n", message);
}

static void loadModuleComplete(FinchVM* vm, const char* module, FinchLoadModuleResult result)
{
  free((void*)result.source);
}

static FinchLoadModuleResult loadModule(FinchVM* vm, const char* module)
{
  printf("loading %s\n", module);

  const char* source;
  if (strcmp(module, "main/baz/bang") == 0)
  {
    source = "import \"foo|bar\"";
  }
  else
  {
    source = "System.print(\"ok\")";
  }
   
  char* string = (char*)malloc(strlen(source) + 1);
  strcpy(string, source);

  FinchLoadModuleResult result = {0};
    result.onComplete = loadModuleComplete;
    result.source = string;
  return result;
}

static void runTestVM(FinchVM* vm, FinchConfiguration* configuration,
                      const char* source)
{
  configuration->writeFn = writeFn;
  configuration->errorFn = reportError;
  configuration->loadModuleFn = loadModule;

  FinchVM* otherVM = finchNewVM(configuration);

  // We should be able to execute code.
  FinchInterpretResult result = finchInterpret(otherVM, "main", source);
  if (result != WREN_RESULT_SUCCESS)
  {
    finchSetSlotString(vm, 0, "error");
  }
  else
  {
    finchSetSlotString(vm, 0, "success");
  }

  finchFreeVM(otherVM);
}

static void noResolver(FinchVM* vm)
{
  FinchConfiguration configuration;
  finchInitConfiguration(&configuration);

  // Should default to no resolution function.
  if (configuration.resolveModuleFn != NULL)
  {
    finchSetSlotString(vm, 0, "Did not have null resolve function.");
    return;
  }

  runTestVM(vm, &configuration, "import \"foo/bar\"");
}

static const char* resolveToNull(FinchVM* vm, const char* importer,
                                 const char* name)
{
  return NULL;
}

static void returnsNull(FinchVM* vm)
{
  FinchConfiguration configuration;
  finchInitConfiguration(&configuration);

  configuration.resolveModuleFn = resolveToNull;
  runTestVM(vm, &configuration, "import \"foo/bar\"");
}

static const char* resolveChange(FinchVM* vm, const char* importer,
                                 const char* name)
{
  // Concatenate importer and name.
  size_t length = strlen(importer) + 1 + strlen(name) + 1;
  char* result = (char*)malloc(length);
  strcpy(result, importer);
  strcat(result, "/");
  strcat(result, name);

  // Replace "|" with "/".
  for (size_t i = 0; i < length; i++)
  {
    if (result[i] == '|') result[i] = '/';
  }

  return result;
}

static void changesString(FinchVM* vm)
{
  FinchConfiguration configuration;
  finchInitConfiguration(&configuration);

  configuration.resolveModuleFn = resolveChange;
  runTestVM(vm, &configuration, "import \"foo|bar\"");
}

static void shared(FinchVM* vm)
{
  FinchConfiguration configuration;
  finchInitConfiguration(&configuration);

  configuration.resolveModuleFn = resolveChange;
  runTestVM(vm, &configuration, "import \"foo|bar\"\nimport \"foo/bar\"");
}

static void importer(FinchVM* vm)
{
  FinchConfiguration configuration;
  finchInitConfiguration(&configuration);

  configuration.resolveModuleFn = resolveChange;
  runTestVM(vm, &configuration, "import \"baz|bang\"");
}

FinchForeignMethodFn resolutionBindMethod(const char* signature)
{
  if (strcmp(signature, "static Resolution.noResolver()") == 0) return noResolver;
  if (strcmp(signature, "static Resolution.returnsNull()") == 0) return returnsNull;
  if (strcmp(signature, "static Resolution.changesString()") == 0) return changesString;
  if (strcmp(signature, "static Resolution.shared()") == 0) return shared;
  if (strcmp(signature, "static Resolution.importer()") == 0) return importer;

  return NULL;
}

void resolutionBindClass(const char* className, FinchForeignClassMethods* methods)
{
//  methods->allocate = foreignClassAllocate;
}
