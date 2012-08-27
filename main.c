#include <allegro5/allegro.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  if (!al_init()) {
    fprintf(stderr, "failed to initialize allegro!\n");
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

  al_register_event_source(
      event_queue,
      al_get_display_event_source(display)
      );

  al_clear_to_color(al_map_rgb(0,100,0));
  al_flip_display();

  for (;;) {
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      break;
    }
  }

  al_destroy_display(display);

  return 0;
}
