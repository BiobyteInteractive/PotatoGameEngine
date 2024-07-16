#include <stdio.h>
#include <string.h>

#include "slots.h"

static void noSet(FinchVM* vm)
{
  // Do nothing.
}

static void getSlots(FinchVM* vm)
{
  bool result = true;
  if (finchGetSlotBool(vm, 1) != true) result = false;

  int length;
  const char* bytes = finchGetSlotBytes(vm, 2, &length);
  if (length != 5) result = false;
  if (memcmp(bytes, "by\0te", length) != 0) result = false;

  if (finchGetSlotDouble(vm, 3) != 1.5) result = false;
  if (strcmp(finchGetSlotString(vm, 4), "str") != 0) result = false;

  FinchHandle* handle = finchGetSlotHandle(vm, 5);

  if (result)
  {
    // Otherwise, return the value so we can tell if we captured it correctly.
    finchSetSlotHandle(vm, 0, handle);
  }
  else
  {
    // If anything failed, return false.
    finchSetSlotBool(vm, 0, false);
  }

  finchReleaseHandle(vm, handle);
}

static void setSlots(FinchVM* vm)
{
  FinchHandle* handle = finchGetSlotHandle(vm, 1);

  finchSetSlotBool(vm, 1, true);
  finchSetSlotBytes(vm, 2, "by\0te", 5);
  finchSetSlotDouble(vm, 3, 1.5);
  finchSetSlotString(vm, 4, "str");
  finchSetSlotNull(vm, 5);

  // Read the slots back to make sure they were set correctly.

  bool result = true;
  if (finchGetSlotBool(vm, 1) != true) result = false;

  int length;
  const char* bytes = finchGetSlotBytes(vm, 2, &length);
  if (length != 5) result = false;
  if (memcmp(bytes, "by\0te", length) != 0) result = false;

  if (finchGetSlotDouble(vm, 3) != 1.5) result = false;
  if (strcmp(finchGetSlotString(vm, 4), "str") != 0) result = false;

  if (finchGetSlotType(vm, 5) != WREN_TYPE_NULL) result = false;

  if (result)
  {
    // Move the value into the return position.
    finchSetSlotHandle(vm, 0, handle);
  }
  else
  {
    // If anything failed, return false.
    finchSetSlotBool(vm, 0, false);
  }

  finchReleaseHandle(vm, handle);
}

static void slotTypes(FinchVM* vm)
{
  bool result =
      finchGetSlotType(vm, 1) == WREN_TYPE_BOOL &&
      finchGetSlotType(vm, 2) == WREN_TYPE_FOREIGN &&
      finchGetSlotType(vm, 3) == WREN_TYPE_LIST &&
      finchGetSlotType(vm, 4) == WREN_TYPE_MAP &&
      finchGetSlotType(vm, 5) == WREN_TYPE_NULL &&
      finchGetSlotType(vm, 6) == WREN_TYPE_NUM &&
      finchGetSlotType(vm, 7) == WREN_TYPE_STRING &&
      finchGetSlotType(vm, 8) == WREN_TYPE_UNKNOWN;

  finchSetSlotBool(vm, 0, result);
}

static void ensure(FinchVM* vm)
{
  int before = finchGetSlotCount(vm);

  finchEnsureSlots(vm, 20);

  int after = finchGetSlotCount(vm);

  // Use the slots to make sure they're available.
  for (int i = 0; i < 20; i++)
  {
    finchSetSlotDouble(vm, i, i);
  }

  int sum = 0;

  for (int i = 0; i < 20; i++)
  {
    sum += (int)finchGetSlotDouble(vm, i);
  }

  char result[100];
  sprintf(result, "%d -> %d (%d)", before, after, sum);
  finchSetSlotString(vm, 0, result);
}

static void ensureOutsideForeign(FinchVM* vm)
{
  // To test the behavior outside of a foreign method (which we're currently
  // in), create a new separate VM.
  FinchConfiguration config;
  finchInitConfiguration(&config);
  FinchVM* otherVM = finchNewVM(&config);

  int before = finchGetSlotCount(otherVM);

  finchEnsureSlots(otherVM, 20);

  int after = finchGetSlotCount(otherVM);

  // Use the slots to make sure they're available.
  for (int i = 0; i < 20; i++)
  {
    finchSetSlotDouble(otherVM, i, i);
  }

  int sum = 0;

  for (int i = 0; i < 20; i++)
  {
    sum += (int)finchGetSlotDouble(otherVM, i);
  }

  finchFreeVM(otherVM);

  char result[100];
  sprintf(result, "%d -> %d (%d)", before, after, sum);
  finchSetSlotString(vm, 0, result);
}

static void foreignClassAllocate(FinchVM* vm)
{
  finchSetSlotNewForeign(vm, 0, 0, 4);
}

static void getListCount(FinchVM* vm)
{
  finchSetSlotDouble(vm, 0, finchGetListCount(vm, 1));
}

static void getListElement(FinchVM* vm)
{
  int index = (int)finchGetSlotDouble(vm, 2);
  finchGetListElement(vm, 1, index, 0);
}

static void getMapValue(FinchVM* vm)
{
  finchGetMapValue(vm, 1, 2, 0);
}

FinchForeignMethodFn slotsBindMethod(const char* signature)
{
  if (strcmp(signature, "static Slots.noSet") == 0) return noSet;
  if (strcmp(signature, "static Slots.getSlots(_,_,_,_,_)") == 0) return getSlots;
  if (strcmp(signature, "static Slots.setSlots(_,_,_,_,_)") == 0) return setSlots;
  if (strcmp(signature, "static Slots.slotTypes(_,_,_,_,_,_,_,_)") == 0) return slotTypes;
  if (strcmp(signature, "static Slots.ensure()") == 0) return ensure;
  if (strcmp(signature, "static Slots.ensureOutsideForeign()") == 0) return ensureOutsideForeign;
  if (strcmp(signature, "static Slots.getListCount(_)") == 0) return getListCount;
  if (strcmp(signature, "static Slots.getListElement(_,_)") == 0) return getListElement;
  if (strcmp(signature, "static Slots.getMapValue(_,_)") == 0) return getMapValue;

  return NULL;
}

void slotsBindClass(const char* className, FinchForeignClassMethods* methods)
{
  methods->allocate = foreignClassAllocate;
}
