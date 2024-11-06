#include <allegro5/allegro.h>

#include "cell.hpp"
#include "common.hpp"

Cell::Cell(Point<float> center, float w, float h)
    : r_(center, w, h, COLOR_BLACK, COLOR_LIGHT_GREY),
      isBomb_(false),
      visible_(false),
      marked_(false),
      bombNeighborCount_(0),
      textNeighborBombCount_("", center) {}

void Cell::setBomb(bool bomb) {
    isBomb_ = bomb;
}

void Cell::setNeighborBombCount(int count) {
    bombNeighborCount_ = count;
}

void Cell::setNeighbors(const std::vector<Cell*>& neighborCells) {
    neighbors_ = neighborCells;
}

void Cell::toggleMark() {
    if (!visible_) {
        marked_ = !marked_;
    }
}

void Cell::draw() {
    if (visible_) {
        r_.setFillColor(COLOR_GREY);
        if (isBomb_) {
            r_.setFillColor(COLOR_RED);
        }
    } else {
        r_.setFillColor(COLOR_LIGHT_GREY);
        if (marked_) {
            r_.setFillColor(COLOR_YELLOW);
        }
    }

    r_.draw();

    if (visible_ && !isBomb_ && bombNeighborCount_ > 0) {
        textNeighborBombCount_.setString(std::to_string(bombNeighborCount_));
        textNeighborBombCount_.setCenter(r_.getCenter());
        textNeighborBombCount_.setColor(getNumberColor(bombNeighborCount_));
        textNeighborBombCount_.draw();
    }
}

ALLEGRO_COLOR Cell::getNumberColor(int number) {
    switch (number) {
        case 1:
            return COLOR_BLUE;
        case 2:
            return COLOR_GREEN;
        case 3:
            return COLOR_RED;
        case 4:
            return COLOR_PURPLE;
        case 5:
            return COLOR_ORANGE;
        case 6:
            return COLOR_CYAN;
        case 7:
            return COLOR_BLACK;
        case 8:
            return COLOR_GREY;
        default:
            return COLOR_BLACK;
    }
}

void Cell::reveal() {
    if (!visible_ && !marked_) {
        visible_ = true;
        if (!isBomb_ && bombNeighborCount_ == 0) {
            for (Cell* neighbor : neighbors_) {
                neighbor->reveal();
            }
        }
    }
}

void Cell::calculateBombNeighbors() {
    bombNeighborCount_ = 0;
    for (Cell* neighbor : neighbors_) {
        if (neighbor->isBombCell()) {
            ++bombNeighborCount_;
        }
    }
}

bool Cell::isVisible() const {
    return visible_;
}

bool Cell::isMarked() const {
    return marked_;
}

bool Cell::isBombCell() const {
    return isBomb_;
}

int Cell::getNeighborBombCount() const {
    return bombNeighborCount_;
}

Point<float> Cell::getCenter() const {
    return r_.getCenter();
}

void Cell::mouseMove(Point<float> mouseLoc) {
    if (r_.contains(mouseLoc)) {
        r_.setFrameColor(COLOR_RED);
    } else {
        r_.setFrameColor(COLOR_BLACK);
    }
}

void Cell::mouseClick(Point<float> mouseLoc, bool rightClick) {
    if (r_.contains(mouseLoc)) {
        if (rightClick) {
            toggleMark();
        } else if (!marked_) {
            reveal();
        }
    }
}