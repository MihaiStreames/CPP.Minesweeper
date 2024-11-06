#include <allegro5/allegro_primitives.h>

#include "rectangle.hpp"

Rectangle::Rectangle(Point<float> rectCenter, float rectW, float rectH, ALLEGRO_COLOR rectFrameColor, ALLEGRO_COLOR rectFillColor)
    : center_(rectCenter), width_(rectW), height_(rectH), frameColor_(rectFrameColor), fillColor_(rectFillColor) {}

void Rectangle::draw() {
    float x1 = center_.x - width_ / 2;
    float y1 = center_.y - height_ / 2;
    float x2 = center_.x + width_ / 2;
    float y2 = center_.y + height_ / 2;

    al_draw_filled_rectangle(x1, y1, x2, y2, fillColor_);
    al_draw_rectangle(x1, y1, x2, y2, frameColor_, 1);
}

void Rectangle::setFillColor(ALLEGRO_COLOR newFillColor) {
    fillColor_ = newFillColor;
}

void Rectangle::setFrameColor(ALLEGRO_COLOR newFrameColor) {
    frameColor_ = newFrameColor;
}

Point<float> Rectangle::getCenter() const {
    return center_;
}

bool Rectangle::contains(Point<float> p) const {
    return p.x >= (center_.x - width_ / 2) &&
           p.x <= (center_.x + width_ / 2) &&
           p.y >= (center_.y - height_ / 2) &&
           p.y <= (center_.y + height_ / 2);
}