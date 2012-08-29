#include "player.h"
#include <stdlib.h>

struct Player *player_new() {
  struct Player *player;
  player = malloc(sizeof(struct Player));

  player->x = 640/2 - 32;
  player->y = 480 - 70;
  player->lives = 3;

  return player;
}

void player_destroy(struct Player *player) {
  free(player);
}

