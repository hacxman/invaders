#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <allegro5/allegro.h>

struct Player {
  int x;
  int y;
  int lives;
  ALLEGRO_BITMAP *obrazok;
};

// vyrobi noveho playera
struct Player *player_new();
// znici playera
void player_destroy(struct Player* player);
// vykresli player
void player_draw(struct Player* player);

#endif

