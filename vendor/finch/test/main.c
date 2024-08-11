#include "./test.h"
#include "./api/api_tests.h"

#include <stdio.h>
#include <string.h>

static FinchVM* vm = NULL;

//This is a simple test runner that serves one purpose:
//To run the language level tests and benchmarks for Finch.
//It is not a general purpose vm or REPL.
//See finch-cli if you're looking for that.

static FinchVM* initVM(bool isAPITest)
{
  FinchConfiguration config;
  finchInitConfiguration(&config);

  config.resolveModuleFn = resolveModule;
  config.loadModuleFn = readModule;
  config.writeFn = vm_write;
  config.errorFn = reportError;

  if(isAPITest) {
    config.bindForeignClassFn = APITest_bindForeignClass;
    config.bindForeignMethodFn = APITest_bindForeignMethod;
  }

  // Since we're running in a standalone process, be generous with memory.
  config.initialHeapSize = 1024 * 1024 * 100;
  return finchNewVM(&config);
}

int main(int argc, const char* argv[]) {

  int handled = handle_args(argc, argv);
  if(handled != 0) return handled;

  int exitCode = 0;
  const char* testName = argv[1];
  bool isAPITest = isModuleAnAPITest(testName);

  vm = initVM(isAPITest);
  FinchInterpretResult result = runFile(vm, testName);

  if(isAPITest) {
    exitCode = APITest_Run(vm, testName);
  }

  if (result == WREN_RESULT_COMPILE_ERROR) return WREN_EX_DATAERR;
  if (result == WREN_RESULT_RUNTIME_ERROR) return WREN_EX_SOFTWARE;

  finchFreeVM(vm);

  return exitCode;

}

