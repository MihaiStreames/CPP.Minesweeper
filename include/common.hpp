#ifndef COMMON_HPP
#define COMMON_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

// Window dimensions
extern int windowWidth;
extern int windowHeight;
extern float mid_x;
extern float mid_y;
extern const double refreshPerSecond;

// Colors
extern const ALLEGRO_COLOR COLOR_RED;
extern const ALLEGRO_COLOR COLOR_GREY;
extern const ALLEGRO_COLOR COLOR_GREEN;
extern const ALLEGRO_COLOR COLOR_YELLOW;
extern const ALLEGRO_COLOR COLOR_BLACK;
extern const ALLEGRO_COLOR COLOR_WHITE;
extern const ALLEGRO_COLOR COLOR_PINK;
extern const ALLEGRO_COLOR COLOR_MAGENTA;
extern const ALLEGRO_COLOR COLOR_DARK_GREY;
extern const ALLEGRO_COLOR COLOR_LIGHT_GREY;
extern const ALLEGRO_COLOR COLOR_BLUE;
extern const ALLEGRO_COLOR COLOR_ORANGE;
extern const ALLEGRO_COLOR COLOR_PURPLE;
extern const ALLEGRO_COLOR COLOR_CYAN;

// Font
extern const int FONT_SIZE;
extern ALLEGRO_FONT* font;

#endif // COMMON_HPP