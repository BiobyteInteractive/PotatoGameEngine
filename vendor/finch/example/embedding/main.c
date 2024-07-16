//For more details, visit https://finch.io/embedding/

#include <stdio.h>
#include "finch.h"

static void writeFn(FinchVM* vm, const char* text)
{
  printf("%s", text);
}

void errorFn(FinchVM* vm, FinchErrorType errorType,
             const char* module, const int line,
             const char* msg)
{
  switch (errorType)
  {
    case WREN_ERROR_COMPILE:
    {
      printf("[%s line %d] [Error] %s\n", module, line, msg);
    } break;
    case WREN_ERROR_STACK_TRACE:
    {
      printf("[%s line %d] in %s\n", module, line, msg);
    } break;
    case WREN_ERROR_RUNTIME:
    {
      printf("[Runtime Error] %s\n", msg);
    } break;
  }
}

int main()
{

  FinchConfiguration config;
  finchInitConfiguration(&config);
    config.writeFn = &writeFn;
    config.errorFn = &errorFn;
  FinchVM* vm = finchNewVM(&config);

  const char* module = "main";
  const char* script = "System.print(\"I am running in a VM!\")";

  FinchInterpretResult result = finchInterpret(vm, module, script);

  switch (result)
  {
    case WREN_RESULT_COMPILE_ERROR:
      { printf("Compile Error!\n"); } break;
    case WREN_RESULT_RUNTIME_ERROR:
      { printf("Runtime Error!\n"); } break;
    case WREN_RESULT_SUCCESS:
      { printf("Success!\n"); } break;
  }

  finchFreeVM(vm);

}