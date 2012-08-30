#include "player.h"
#include <stdlib.h>
#include <stdio.h>

struct Player * player_copy(struct Player * player) {
  struct Player * p = player_new();

  p->x = player->x;
  p->y = player->y;
  p->lives = player->lives;

  return p;
}

void player_draw(struct Player *player) {
  al_draw_bitmap(player->obrazok, player->x, player->y, 0);
}

struct Player *player_new() {
  struct Player *player;
  player = malloc(sizeof(struct Player));

  player->x = 640/2 - 32;
  player->y = 480 - 70;
  player->lives = 3;

  ALLEGRO_BITMAP *obrazok = NULL;
  obrazok = al_load_bitmap("obrazok.png");
  if (!obrazok) {
    fprintf(stderr, "beda sa stala!!!11!11 :( obrazok sa stratil!1!1\n");
    return;
  }
  player->obrazok = obrazok;

  return player;
}

void player_destroy(struct Player *player) {
  al_destroy_bitmap(player->obrazok);
  free(player);
}

