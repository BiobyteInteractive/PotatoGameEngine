#include <string.h>

#include "maps.h"

static void newMap(FinchVM* vm)
{
  finchSetSlotNewMap(vm, 0);
}

static void invalidInsert(FinchVM* vm)
{
  finchSetSlotNewMap(vm, 0);
  
  finchEnsureSlots(vm, 3);
  // Foreign Class is in slot 1
  finchSetSlotString(vm, 2, "England");
  finchSetMapValue(vm, 0, 1, 2); // expect this to cause errors
}

static void insert(FinchVM* vm)
{
  finchSetSlotNewMap(vm, 0);
  
  finchEnsureSlots(vm, 3);

  // Insert String
  finchSetSlotString(vm, 1, "England");
  finchSetSlotString(vm, 2, "London");
  finchSetMapValue(vm, 0, 1, 2);

  // Insert Double
  finchSetSlotDouble(vm, 1, 1.0);
  finchSetSlotDouble(vm, 2, 42.0);
  finchSetMapValue(vm, 0, 1, 2);

  // Insert Boolean
  finchSetSlotBool(vm, 1, false);
  finchSetSlotBool(vm, 2, true);
  finchSetMapValue(vm, 0, 1, 2);

  // Insert Null
  finchSetSlotNull(vm, 1);
  finchSetSlotNull(vm, 2);
  finchSetMapValue(vm, 0, 1, 2);

  // Insert List
  finchSetSlotString(vm, 1, "Empty");
  finchSetSlotNewList(vm, 2);
  finchSetMapValue(vm, 0, 1, 2);
}

static void removeKey(FinchVM* vm)
{
  finchEnsureSlots(vm, 3);

  finchSetSlotString(vm, 2, "key");
  finchRemoveMapValue(vm, 1, 2, 0);
}

static void countFinch(FinchVM* vm)
{
  int count = finchGetMapCount(vm, 1);
  finchSetSlotDouble(vm, 0, count);
}

static void countAPI(FinchVM* vm)
{
  insert(vm);
  int count = finchGetMapCount(vm, 0);
  finchSetSlotDouble(vm, 0, count);
}

static void containsFinch(FinchVM* vm)
{
  bool result = finchGetMapContainsKey(vm, 1, 2);
  finchSetSlotBool(vm, 0, result);
}


static void containsAPI(FinchVM* vm)
{
  insert(vm);
  
  finchEnsureSlots(vm, 1);
  finchSetSlotString(vm, 1, "England");

  bool result = finchGetMapContainsKey(vm, 0, 1);
  finchSetSlotBool(vm, 0, result);
}

static void containsAPIFalse(FinchVM* vm)
{
  insert(vm);

  finchEnsureSlots(vm, 1);
  finchSetSlotString(vm, 1, "DefinitelyNotARealKey");

  bool result = finchGetMapContainsKey(vm, 0, 1);
  finchSetSlotBool(vm, 0, result);
}


FinchForeignMethodFn mapsBindMethod(const char* signature)
{
  if (strcmp(signature, "static Maps.newMap()") == 0) return newMap;
  if (strcmp(signature, "static Maps.insert()") == 0) return insert;
  if (strcmp(signature, "static Maps.remove(_)") == 0) return removeKey;
  if (strcmp(signature, "static Maps.count(_)") == 0) return countFinch;
  if (strcmp(signature, "static Maps.count()") == 0) return countAPI;
  if (strcmp(signature, "static Maps.contains()") == 0) return containsAPI;
  if (strcmp(signature, "static Maps.containsFalse()") == 0) return containsAPIFalse;
  if (strcmp(signature, "static Maps.contains(_,_)") == 0) return containsFinch;
  if (strcmp(signature, "static Maps.invalidInsert(_)") == 0) return invalidInsert;

  return NULL;
}

void foreignAllocate(FinchVM* vm) {
  finchSetSlotNewForeign(vm, 0, 0, 0);
}

void mapBindClass(
    const char* className, FinchForeignClassMethods* methods)
{
  if (strcmp(className, "ForeignClass") == 0)
  {
    methods->allocate = foreignAllocate;
    return;
  }
}
