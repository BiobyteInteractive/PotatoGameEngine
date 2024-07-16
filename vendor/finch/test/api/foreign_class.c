#include <stdio.h>
#include <string.h>

#include "foreign_class.h"

static int finalized = 0;

static void apiFinalized(FinchVM* vm)
{
  finchSetSlotDouble(vm, 0, finalized);
}

static void counterAllocate(FinchVM* vm)
{
  double* value = (double*)finchSetSlotNewForeign(vm, 0, 0, sizeof(double));
  *value = 0;
}

static void counterIncrement(FinchVM* vm)
{
  double* value = (double*)finchGetSlotForeign(vm, 0);
  double increment = finchGetSlotDouble(vm, 1);

  *value += increment;
}

static void counterValue(FinchVM* vm)
{
  double value = *(double*)finchGetSlotForeign(vm, 0);
  finchSetSlotDouble(vm, 0, value);
}

static void pointAllocate(FinchVM* vm)
{
  double* coordinates = (double*)finchSetSlotNewForeign(vm, 0, 0, sizeof(double[3]));

  // This gets called by both constructors, so sniff the slot count to see
  // which one was invoked.
  if (finchGetSlotCount(vm) == 1)
  {
    coordinates[0] = 0.0;
    coordinates[1] = 0.0;
    coordinates[2] = 0.0;
  }
  else
  {
    coordinates[0] = finchGetSlotDouble(vm, 1);
    coordinates[1] = finchGetSlotDouble(vm, 2);
    coordinates[2] = finchGetSlotDouble(vm, 3);
  }
}

static void pointTranslate(FinchVM* vm)
{
  double* coordinates = (double*)finchGetSlotForeign(vm, 0);
  coordinates[0] += finchGetSlotDouble(vm, 1);
  coordinates[1] += finchGetSlotDouble(vm, 2);
  coordinates[2] += finchGetSlotDouble(vm, 3);
}

static void pointToString(FinchVM* vm)
{
  double* coordinates = (double*)finchGetSlotForeign(vm, 0);
  char result[100];
  sprintf(result, "(%g, %g, %g)",
      coordinates[0], coordinates[1], coordinates[2]);
  finchSetSlotString(vm, 0, result);
}

static void resourceAllocate(FinchVM* vm)
{
  int* value = (int*)finchSetSlotNewForeign(vm, 0, 0, sizeof(int));
  *value = 123;
}

static void resourceFinalize(void* data)
{
  // Make sure we get the right data back.
  int* value = (int*)data;
  if (*value != 123) exit(1);

  finalized++;
}

static void badClassAllocate(FinchVM* vm)
{
  finchEnsureSlots(vm, 1);
  finchSetSlotString(vm, 0, "Something went wrong");
  finchAbortFiber(vm, 0);
}

FinchForeignMethodFn foreignClassBindMethod(const char* signature)
{
  if (strcmp(signature, "static ForeignClass.finalized") == 0) return apiFinalized;
  if (strcmp(signature, "Counter.increment(_)") == 0) return counterIncrement;
  if (strcmp(signature, "Counter.value") == 0) return counterValue;
  if (strcmp(signature, "Point.translate(_,_,_)") == 0) return pointTranslate;
  if (strcmp(signature, "Point.toString") == 0) return pointToString;

  return NULL;
}

void foreignClassBindClass(
    const char* className, FinchForeignClassMethods* methods)
{
  if (strcmp(className, "Counter") == 0)
  {
    methods->allocate = counterAllocate;
    return;
  }

  if (strcmp(className, "Point") == 0)
  {
    methods->allocate = pointAllocate;
    return;
  }

  if (strcmp(className, "Resource") == 0)
  {
    methods->allocate = resourceAllocate;
    methods->finalize = resourceFinalize;
    return;
  }

  if (strcmp(className, "BadClass") == 0)
  {
    methods->allocate = badClassAllocate;
    return;
  }
}
