#include <string.h>

#include "lists.h"

static void newList(FinchVM* vm)
{
  finchSetSlotNewList(vm, 0);
}

// Helper function to store a double in a slot then insert it into the list at
// slot zero.
static void insertNumber(FinchVM* vm, int index, double value)
{
  finchSetSlotDouble(vm, 1, value);
  finchInsertInList(vm, 0, index, 1);
}

// Helper function to append a double in a slot then insert it into the list at
// slot zero.
static void appendNumber(FinchVM* vm, double value)
{
  finchSetSlotDouble(vm, 1, value);
  finchInsertInList(vm, 0, -1, 1);
}

static void insert(FinchVM* vm)
{
  finchSetSlotNewList(vm, 0);

  finchEnsureSlots(vm, 2);

  // Appending.
  insertNumber(vm, 0, 1.0);
  insertNumber(vm, 1, 2.0);
  insertNumber(vm, 2, 3.0);

  // Inserting.
  insertNumber(vm, 0, 4.0);
  insertNumber(vm, 1, 5.0);
  insertNumber(vm, 2, 6.0);

  // Negative indexes.
  insertNumber(vm, -1, 7.0);
  insertNumber(vm, -2, 8.0);
  insertNumber(vm, -3, 9.0);
}

static void get(FinchVM* vm)
{
  int listSlot = 1;
  int index = (int)finchGetSlotDouble(vm, 2);

  finchGetListElement(vm, listSlot, index, 0);
}

static void set(FinchVM* vm)
{
  finchSetSlotNewList(vm, 0);

  finchEnsureSlots(vm, 2);

  appendNumber(vm, 1.0);
  appendNumber(vm, 2.0);
  appendNumber(vm, 3.0);
  appendNumber(vm, 4.0);
  
  //list[2] = 33
  finchSetSlotDouble(vm, 1, 33);
  finchSetListElement(vm, 0, 2, 1);

  //list[-1] = 44
  finchSetSlotDouble(vm, 1, 44);
  finchSetListElement(vm, 0, -1, 1);
}

FinchForeignMethodFn listsBindMethod(const char* signature)
{
  if (strcmp(signature, "static Lists.newList()") == 0) return newList;
  if (strcmp(signature, "static Lists.insert()") == 0) return insert;
  if (strcmp(signature, "static Lists.set()") == 0) return set;
  if (strcmp(signature, "static Lists.get(_,_)") == 0) return get;

  return NULL;
}
