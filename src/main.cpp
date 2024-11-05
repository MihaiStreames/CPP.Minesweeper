#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "common.hpp"
#include "canvas.hpp"

void must_init(bool test, const char* description) {
    if (test) return;
    std::cerr << "Couldn't initialize " << description << '\n';
    exit(1);
}

void must_init(void* test, const char* description) {
    must_init(test != nullptr, description);
}

int main() {
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / refreshPerSecond);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_DISPLAY* disp = al_create_display(windowWidth, windowHeight);
    must_init(disp, "display");

    must_init(al_init_ttf_addon(), "TTF addon");
    font = al_load_ttf_font("assets/SourceCodePro-Regular.ttf", FONT_SIZE, 0);
    if (!font) {
        std::cerr << "Could not load font from 'assets/SourceCodePro-Regular.ttf'. Using built-in font.\n";
        font = al_create_builtin_font(); // Use built-in font if TTF font not found
    }
    must_init(font, "font");

    must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    srand(static_cast<unsigned>(time(nullptr)));

    bool done = false;
    bool draw = false;
    ALLEGRO_EVENT event;
    Canvas canvas;

    al_start_timer(timer);
    while (!done) {
        al_wait_for_event(queue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_KEY_DOWN:
                canvas.keyDown(event.keyboard.keycode);
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                canvas.mouseMove({ static_cast<float>(event.mouse.x), static_cast<float>(event.mouse.y) });
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                canvas.mouseClick({ static_cast<float>(event.mouse.x), static_cast<float>(event.mouse.y) },
                                  event.mouse.button == 2 || event.mouse.button == 3);
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            case ALLEGRO_EVENT_TIMER:
                draw = true;
                break;
            default:
                break;
        }

        if (canvas.shouldExit) {
            done = true; // Exit the main loop gracefully >:3
        }

        if (draw && al_is_event_queue_empty(queue)) {
            draw = false;
            al_clear_to_color(al_map_rgb(255, 255, 255));
            canvas.draw();
            al_flip_display();
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    // al_uninstall_system();

    return 0;
}