#ifndef TEXT_HPP
#define TEXT_HPP

#include <allegro5/allegro_font.h>

#include <string>

#include "point.hpp"
#include "common.hpp"

class Text {
    std::string s_;
    Point center_;
    ALLEGRO_COLOR color_;

public:
    Text(const std::string& text, Point center, ALLEGRO_COLOR color = COLOR_BLACK);

    void draw();
    void setString(const std::string& newString);
    void setCenter(Point newCenter);
    void setColor(ALLEGRO_COLOR newColor);

    Point getCenter() const;
    std::string getString() const;
};

#endif // TEXT_HPP