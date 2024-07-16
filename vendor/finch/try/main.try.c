#include "../test/test.h"

#include <stdio.h>
#include <string.h>

static FinchVM* vm = NULL;

//This is a simple program that exposes finch to the browser
//for https://finch.io/try and runs scripts.

static FinchVM* initVM()
{
  FinchConfiguration config;
  finchInitConfiguration(&config);

  config.resolveModuleFn = resolveModule;
  config.loadModuleFn = readModule;
  config.writeFn = vm_write;
  config.errorFn = reportError;

  // Might be a more reasonable value, 
  // but since this is simple, keep it simple.
  config.initialHeapSize = 1024 * 1024 * 100;
  return finchNewVM(&config);
}

//The endpoint we call from the browser
int finch_compile(const char* input) {
  FinchVM* vm = initVM();
  FinchInterpretResult result = finchInterpret(vm, "compile", input);
  finchFreeVM(vm);
  return (int)result;
}

//Main not used, but required. We call finch_compile directly.
int main(int argc, const char* argv[]) {
  return 0;
}

