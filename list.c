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

struct List *list_deep_copy(struct List* list, void*(*copy)(void*)) {
  if (list == NULL) return NULL;

  struct List * novy = malloc(sizeof(struct List));
  struct List * posledny = novy;

  while (list != NULL) {
    posledny->item = copy(list->item);
    posledny->next = list->next != NULL ? malloc(sizeof(struct List)) : NULL;
    list = list->next;
    posledny = posledny->next;
  }

  return novy;
}

void list_destroy(struct List *list) {
  struct List * iterator = list;
  while (iterator != NULL) {
    struct List * next = iterator->next;
    free(iterator);
    iterator = next;
  }
}
