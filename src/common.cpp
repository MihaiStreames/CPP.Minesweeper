#include "common.hpp"

int windowWidth                 = 500;
int windowHeight                = 550; // Increased height to accommodate timer display
float mid_x                     = static_cast<float>(windowWidth) / 2.0F;
float mid_y                     = static_cast<float>(windowHeight) / 2.0F;
const double refreshPerSecond   = 60;

// Colors
const ALLEGRO_COLOR COLOR_RED           = al_map_rgb(255, 0, 0);
const ALLEGRO_COLOR COLOR_GREY          = al_map_rgb(200, 200, 200);
const ALLEGRO_COLOR COLOR_GREEN         = al_map_rgb(0, 255, 0);
const ALLEGRO_COLOR COLOR_YELLOW        = al_map_rgb(255, 255, 0);
const ALLEGRO_COLOR COLOR_BLACK         = al_map_rgb(0, 0, 0);
const ALLEGRO_COLOR COLOR_WHITE         = al_map_rgb(255, 255, 255);
const ALLEGRO_COLOR COLOR_PINK          = al_map_rgb(200, 150, 167);
const ALLEGRO_COLOR COLOR_MAGENTA       = al_map_rgb(255, 0, 255);
const ALLEGRO_COLOR COLOR_DARK_GREY     = al_map_rgb(169, 169, 169);
const ALLEGRO_COLOR COLOR_LIGHT_GREY    = al_map_rgb(211, 211, 211);
const ALLEGRO_COLOR COLOR_BLUE          = al_map_rgb(0, 0, 255);
const ALLEGRO_COLOR COLOR_ORANGE        = al_map_rgb(255, 165, 0);
const ALLEGRO_COLOR COLOR_PURPLE        = al_map_rgb(128, 0, 128);
const ALLEGRO_COLOR COLOR_CYAN          = al_map_rgb(0, 255, 255);

// Font
const int FONT_SIZE     = 20;
ALLEGRO_FONT* font      = nullptr;