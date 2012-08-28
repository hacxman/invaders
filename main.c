#include <allegro5/allegro.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  if (!al_init()) {
    fprintf(stderr, "failed to initialize allegro!\n");
    return -1;
  }

  if (!al_init_image_addon()) {
    fprintf(stderr, "nende nam addon pre obrazky. buuuu\n");
    return -1;
  }

  ALLEGRO_DISPLAY *display = NULL;
  display = al_create_display(640, 480);
  if (!display) {
    fprintf(stderr, "failed to create display!\n");
    return -1;
  }

  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  event_queue = al_create_event_queue();
  if (!event_queue) {
    fprintf(stderr, "failed to create event queue!\n");
    al_destroy_display(display);
    return -1;
  }

  ALLEGRO_TIMER *timer = NULL;
  timer = al_create_timer(1.0/60.0);
  if (!timer) {
    fprintf(stderr, "failed to create timer!!!11!1\n");
    return -1;
  }

  if (!al_install_keyboard()) {
    fprintf(stderr, "failed to install keyboard, press any key to continue\n");
    return -1;
  }

  al_register_event_source(event_queue,
      al_get_display_event_source(display));
  al_register_event_source(event_queue,
      al_get_timer_event_source(timer));
  al_register_event_source(event_queue,
      al_get_keyboard_event_source());

  al_start_timer(timer);

  al_clear_to_color(al_map_rgb(0,100,0));
  al_flip_display();


  ALLEGRO_BITMAP *obrazok = NULL;
  obrazok = al_load_bitmap("obrazok.png");
  if (!obrazok) {
    fprintf(stderr, "beda sa stala!!!11!11 :( obrazok sa stratil!1!1\n");
    al_destroy_display(display);
    return -1;
  }


  int color = 0, c2 = 0, c3 = 0, x = 100, y = 100;
  bool stlacene_tlacitka[ALLEGRO_KEY_MAX];
  memset(stlacene_tlacitka, 0, sizeof(stlacene_tlacitka));
  for (;;) {
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      break;
    }

    if (event.type == ALLEGRO_EVENT_TIMER) {
      if (stlacene_tlacitka[ALLEGRO_KEY_LEFT]) {
        x = x - 10;
      }
      if (stlacene_tlacitka[ALLEGRO_KEY_RIGHT]) {
        x = x + 10;
      }
      if (stlacene_tlacitka[ALLEGRO_KEY_UP]) {
        y = y - 10;
      }
      if (stlacene_tlacitka[ALLEGRO_KEY_DOWN]) {
        y = y + 10;
      }

      al_clear_to_color(al_map_rgb(c2+=3,c3+=7,color+=5));
      al_draw_bitmap(obrazok, x, y, c2);
      al_flip_display();
    }

    if (event.type == ALLEGRO_EVENT_KEY_DOWN
      ||event.type == ALLEGRO_EVENT_KEY_UP) {

      ALLEGRO_KEYBOARD_STATE stav_klavesnice;
      al_get_keyboard_state(&stav_klavesnice);

      if (al_key_down(&stav_klavesnice, ALLEGRO_KEY_ESCAPE)) {
        exit(0);
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

  al_destroy_timer(timer);
  al_destroy_event_queue(event_queue);
  al_destroy_display(display);

  return 0;
}
