#include <allegro5/allegro.h>

#include <iostream>

#include "text.hpp"

Text::Text(const std::string& text, Point<float> center, ALLEGRO_COLOR color)
    : s_{ text }, center_{ center }, color_{ color } {}

void Text::draw() {
    if (!font) {
        std::cerr << "Error: Font is not initialized or is null!\n";
        return;
    }

    int textWidth = al_get_text_width(font, s_.c_str());
    int textHeight = al_get_font_line_height(font);

    float x = center_.x - static_cast<float>(textWidth) / 2.0f;
    float y = center_.y - static_cast<float>(textHeight) / 2.0f;

    al_draw_text(font, color_, x, y, 0, s_.c_str());
}

void Text::setString(const std::string& newString) {
    s_ = newString;
}

void Text::setCenter(Point<float> newCenter) {
    center_ = newCenter;
}

void Text::setColor(ALLEGRO_COLOR newColor) {
    color_ = newColor;
}

Point<float> Text::getCenter() const {
    return center_;
}

std::string Text::getString() const {
    return s_;
}