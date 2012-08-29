#ifndef _PLAYER_H_
#define _PLAYER_H_

struct Player {
  int x;
  int y;
  int lives;
};

// vyrobi noveho playera
struct Player *player_new();
// znici playera
void player_destroy(struct Player* player);

#endif

