#include <allegro5/allegro.h>
#include <stdio.h>
#include <stdlib.h>

#include "player.h"

const int SCREEN_W = 640;
const int SCREEN_H = 480;

struct Player *player;
ALLEGRO_MUTEX *mutex;

void * kresliace_vlakno(ALLEGRO_THREAD *thread, void *event_queue) {
  ALLEGRO_DISPLAY *display = NULL;
  display = al_create_display(640, 480);
  if (!display) {
    fprintf(stderr, "failed to create display!\n");
    exit(1);
  }

  al_register_event_source(event_queue,
      al_get_display_event_source(display));

  while (!al_get_thread_should_stop(thread)) {
    al_clear_to_color(al_map_rgb(100,0,100));
    int i = 0;

    al_lock_mutex(mutex);
       struct Player * _player = player_copy(player);
    al_unlock_mutex(mutex);

    for (i = 0; i < 300; i++) {
      player_draw(_player);
    }

    player_destroy(_player);
    al_flip_display();
  }

  al_unregister_event_source(event_queue,
      al_get_display_event_source(display));
  al_destroy_display(display);
}

void main_loop(ALLEGRO_EVENT_QUEUE *event_queue) {
  int color = 0, c2 = 0, c3 = 0;
  bool stlacene_tlacitka[ALLEGRO_KEY_MAX];
  memset(stlacene_tlacitka, 0, sizeof(stlacene_tlacitka));

  player = player_new();

  mutex = al_create_mutex();
  ALLEGRO_THREAD *thread = al_create_thread(kresliace_vlakno, event_queue);
  al_start_thread(thread);

  for (;;) {
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      break;
    }

    if (event.type == ALLEGRO_EVENT_TIMER) {
      al_lock_mutex(mutex);

      if (stlacene_tlacitka[ALLEGRO_KEY_LEFT]) {
        player->x = player->x - 10;
        if (player->x < 0) player->x = 0;
      }
      if (stlacene_tlacitka[ALLEGRO_KEY_RIGHT]) {
        player->x = player->x + 10;
        if (player->x > SCREEN_W - 64) player->x = SCREEN_W - 64;
      }

      al_unlock_mutex(mutex);

    }

    if (event.type == ALLEGRO_EVENT_KEY_DOWN
      ||event.type == ALLEGRO_EVENT_KEY_UP) {

      ALLEGRO_KEYBOARD_STATE stav_klavesnice;
      al_get_keyboard_state(&stav_klavesnice);

      if (al_key_down(&stav_klavesnice, ALLEGRO_KEY_ESCAPE)) {
        break;
      }

      if (al_key_down(&stav_klavesnice, ALLEGRO_KEY_LEFT)) {
        stlacene_tlacitka[ALLEGRO_KEY_LEFT] = true;
      } else {
        stlacene_tlacitka[ALLEGRO_KEY_LEFT] = false;
      }
      if (al_key_down(&stav_klavesnice, ALLEGRO_KEY_RIGHT)) {
        stlacene_tlacitka[ALLEGRO_KEY_RIGHT] = true;
      } else {
        stlacene_tlacitka[ALLEGRO_KEY_RIGHT] = false;
      }
      if (al_key_down(&stav_klavesnice, ALLEGRO_KEY_UP)) {
        stlacene_tlacitka[ALLEGRO_KEY_UP] = true;
      } else {
        stlacene_tlacitka[ALLEGRO_KEY_UP] = false;
      }
      if (al_key_down(&stav_klavesnice, ALLEGRO_KEY_DOWN)) {
        stlacene_tlacitka[ALLEGRO_KEY_DOWN] = true;
      } else {
        stlacene_tlacitka[ALLEGRO_KEY_DOWN] = false;
      }
    }
  }

  al_destroy_thread(thread);


}

ALLEGRO_EVENT_QUEUE *init(void) {
  if (!al_init()) {
    fprintf(stderr, "failed to initialize allegro!\n");
    exit(1);
  }

  if (!al_init_image_addon()) {
    fprintf(stderr, "nende nam addon pre obrazky. buuuu\n");
    exit(1);
  }


  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  event_queue = al_create_event_queue();
  if (!event_queue) {
    fprintf(stderr, "failed to create event queue!\n");
//    al_destroy_display(display);
    exit(1);
  }

  ALLEGRO_TIMER *timer = NULL;
  timer = al_create_timer(1.0/60.0);
  if (!timer) {
    fprintf(stderr, "failed to create timer!!!11!1\n");
    exit(1);
  }

  if (!al_install_keyboard()) {
    fprintf(stderr, "failed to install keyboard, press any key to continue\n");
    exit(1);
  }

//  al_register_event_source(event_queue,
//      al_get_display_event_source(display));
  al_register_event_source(event_queue,
      al_get_timer_event_source(timer));
  al_register_event_source(event_queue,
      al_get_keyboard_event_source());

  al_start_timer(timer);

//  al_clear_to_color(al_map_rgb(0,0,0));
//  al_flip_display();

  return event_queue;
}

int main(void) {
  ALLEGRO_EVENT_QUEUE *event_queue = init();

  main_loop(event_queue);

/*  al_destroy_timer(timer);
  al_destroy_event_queue(event_queue);
  al_destroy_display(display);*/

  return 0;
}
