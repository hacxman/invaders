#ifndef _LIST_H_
#define _LIST_H_

#include <assert.h>
#include <stdlib.h>

struct List {
  void * item;
  struct List * next;
};

void list_add(struct List ** list, void * item);
void list_remove(struct List **list, void *data);
struct List *list_deep_copy(struct List* list, void*(*copy)(void*));
void list_destroy(struct List *list);

#endif

