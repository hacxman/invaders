#include "list.h"

void list_add(struct List ** list, void * item) {
  assert(list);

  struct List * newone = malloc(sizeof(struct List));
  newone->item = item;
  newone->next = *list;
  *list = newone;
}

void list_remove(struct List **list, void *data) {
  struct List *removed;

  while(1) {
    if ((*list)->item == data) {
      removed = *list;
      *list = removed->next;
      free(removed);
      return;
    }
    list = &(*list) -> next;
  }
}

