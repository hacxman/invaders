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

  al_register_event_source(
      event_queue,
      al_get_display_event_source(display)
      );
  al_register_event_source(
      event_queue,
      al_get_timer_event_source(timer)
      );

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


  int color = 0, c2 = 0, c3 = 0;
  for (;;) {
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      break;
    }

    if (event.type == ALLEGRO_EVENT_TIMER) {
      al_clear_to_color(al_map_rgb(c2+=3,c3+=7,color+=5));
      al_draw_bitmap(obrazok, 100, 100, c2);
      al_flip_display();
    }

  }

  al_destroy_timer(timer);
  al_destroy_event_queue(event_queue);
  al_destroy_display(display);

  return 0;
}
