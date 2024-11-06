#ifndef CELL_HPP
#define CELL_HPP

#include <vector>

#include "rectangle.hpp"
#include "text.hpp"

class Cell {
    Rectangle r_;
    bool isBomb_;
    bool visible_;
    bool marked_;
    int bombNeighborCount_;
    Text textNeighborBombCount_;
    std::vector<Cell*> neighbors_;

public:
    Cell(Point<float> center, float w, float h);

    void setBomb(bool bomb);
    void setNeighborBombCount(int count);
    void setNeighbors(const std::vector<Cell*>& neighborCells);
    void toggleMark();
    void draw();
    void reveal();
    void calculateBombNeighbors();

    bool isVisible() const;
    bool isMarked() const;
    bool isBombCell() const;
    int getNeighborBombCount() const;
    Point<float> getCenter() const;

    void mouseMove(Point<float> mouseLoc);
    void mouseClick(Point<float> mouseLoc, bool rightClick);

private:
    ALLEGRO_COLOR getNumberColor(int number);
};

#endif // CELL_HPP