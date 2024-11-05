#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <allegro5/color.h>

#include "point.hpp"
#include "common.hpp"

class Rectangle {
    Point center_;
    float width_;
    float height_;
    ALLEGRO_COLOR frameColor_;
    ALLEGRO_COLOR fillColor_;

public:
    Rectangle(Point rectCenter, float rectW, float rectH, ALLEGRO_COLOR rectFrameColor = COLOR_BLACK, ALLEGRO_COLOR rectFillColor = COLOR_WHITE);

    void draw();
    void setFillColor(ALLEGRO_COLOR newFillColor);
    void setFrameColor(ALLEGRO_COLOR newFrameColor);
    Point getCenter() const;
    bool contains(Point p) const;
};

#endif // RECTANGLE_HPP