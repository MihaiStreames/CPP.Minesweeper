#include <cstdlib>

#include "grid.hpp"

Grid::Grid(int gridSize, float cellW, float cellH)
    : size_(gridSize),
      cellWidth_(cellW),
      cellHeight_(cellH),
      totalMines_(0) {
    float cellMargin = 3.0f;
    float adjustedCellWidth = cellWidth_ - cellMargin;
    float adjustedCellHeight = cellHeight_ - cellMargin;

    cells_.resize(size_);
    for (int i = 0; i < size_; ++i) {
        cells_[i].reserve(size_);
        for (int j = 0; j < size_; ++j) {
            Point center = {
                static_cast<float>(j) * cellWidth_ + cellWidth_ / 2,
                static_cast<float>(i) * cellHeight_ + cellHeight_ / 2 + 50 // Offset for timer and mine count
            };
            cells_[i].emplace_back(center, adjustedCellWidth, adjustedCellHeight);
        }
    }

    placeBombs();
    setupNeighbors();
    calculateAllBombNeighbors();
}

void Grid::placeBombs() {
    int numBombs = static_cast<int>(static_cast<double>(size_ * size_) * 0.15 + 0.5);
    totalMines_ = numBombs;
    int placedBombs = 0;

    while (placedBombs < numBombs) {
        int i = rand() % size_;
        int j = rand() % size_;
        if (!cells_[i][j].isBombCell()) {
            cells_[i][j].setBomb(true);
            mines.push_back(&cells_[i][j]);
            ++placedBombs;
        }
    }
}

void Grid::setupNeighbors() {
    for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
            std::vector<Cell*> neighborCells;
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    int ni = i + di;
                    int nj = j + dj;
                    if (di == 0 && dj == 0) continue;
                    if (ni >= 0 && ni < size_ && nj >= 0 && nj < size_) {
                        neighborCells.push_back(&cells_[ni][nj]);
                    }
                }
            }
            cells_[i][j].setNeighbors(neighborCells);
        }
    }
}

void Grid::calculateAllBombNeighbors() {
    for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
            cells_[i][j].calculateBombNeighbors();
        }
    }
}

void Grid::draw() {
    for (auto& row : cells_) {
        for (auto& cell : row) {
            cell.draw();
        }
    }
}

void Grid::mouseMove(Point mouseLoc) {
    for (auto& row : cells_) {
        for (auto& cell : row) {
            cell.mouseMove(mouseLoc);
        }
    }
}

int Grid::mouseClick(Point mouseLoc, bool rightClick) {
    bool bombClicked = false;
    for (auto& row : cells_) {
        for (auto& cell : row) {
            if (cell.getCenter().x - cellWidth_ / 2 <= mouseLoc.x &&
                mouseLoc.x <= cell.getCenter().x + cellWidth_ / 2 &&
                cell.getCenter().y - cellHeight_ / 2 <= mouseLoc.y &&
                mouseLoc.y <= cell.getCenter().y + cellHeight_ / 2) {

                cell.mouseClick(mouseLoc, rightClick);
                if (!rightClick && cell.isBombCell() && cell.isVisible()) {
                    bombClicked = true;
                }
                break;
            }
        }
    }
    if (bombClicked) {
        return -1;
    } else if (checkWinCondition()) {
        return 1;
    } else {
        return 0;
    }
}

int Grid::getTotalMines() const {
    return totalMines_;
}

int Grid::getMarkedCellsCount() const {
    int count = 0;
    for (const auto& row : cells_) {
        for (const auto& cell : row) {
            if (cell.isMarked()) {
                ++count;
            }
        }
    }
    return count;
}

void Grid::reset() {
    totalMines_ = 0;
    mines.clear();
    *this = Grid(size_, cellWidth_, cellHeight_);
}

bool Grid::checkWinCondition() {
    for (const auto& row : cells_) {
        for (const auto& cell : row) {
            if (!cell.isBombCell() && !cell.isVisible()) {
                return false;
            }
        }
    }
    return true;
}