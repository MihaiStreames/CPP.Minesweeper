#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <allegro5/color.h>

#include "point.hpp"
#include "common.hpp"

class Rectangle {
    Point<float> center_;
    float width_;
    float height_;
    ALLEGRO_COLOR frameColor_;
    ALLEGRO_COLOR fillColor_;

public:
    Rectangle(Point<float> rectCenter, float rectW, float rectH, ALLEGRO_COLOR rectFrameColor = COLOR_BLACK, ALLEGRO_COLOR rectFillColor = COLOR_WHITE);

    void draw();
    void setFillColor(ALLEGRO_COLOR newFillColor);
    void setFrameColor(ALLEGRO_COLOR newFrameColor);
    Point<float> getCenter() const;
    bool contains(Point<float> p) const;
};

#endif // RECTANGLE_HPP