#include <cstdlib>

#include "grid.hpp"

using u64 = long unsigned int;

Grid::Grid(int gridSize, int minesCount, float cellW, float cellH)
    : size_(gridSize),
      cellWidth_(cellW),
      cellHeight_(cellH),
      totalMines_(minesCount),
      firstClick_(true)
     {
    float cellMargin = 3.0f;
    float adjustedCellWidth = cellWidth_ - cellMargin;
    float adjustedCellHeight = cellHeight_ - cellMargin;

    cells_.resize(size_);
    for (int i = 0; i < size_; ++i) {
        cells_[i].reserve(size_);
        for (int j = 0; j < size_; ++j) {
            Point<float> center = {
                static_cast<float>(j) * cellWidth_ + cellWidth_ / 2,
                static_cast<float>(i) * cellHeight_ + cellHeight_ / 2 + 50 // Offset for timer and mine count
            };
            cells_[i].emplace_back(center, adjustedCellWidth, adjustedCellHeight);
        }
    }
}

void Grid::placeBombs(Point<u64> first) {
    int placedBombs = 0;
    while (placedBombs < totalMines_) {
        u64 i = rand() % size_;
        u64 j = rand() % size_;
        if (i <= first.x + 1 && first.x <= i + 1 && j <= first.y + 1 && first.y <= j + 1) continue; // Mine cannot be around first click cell
        if (cells_[i][j].isBombCell()) continue;

        cells_[i][j].setBomb(true);
        mines.push_back(&cells_[i][j]);
        ++placedBombs;
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
    for (auto& row : cells_)
        for (auto& cell : row)
            cell.draw();
}

void Grid::mouseMove(Point<float> mouseLoc) {
    for (auto& row : cells_)
        for (auto& cell : row)
            cell.mouseMove(mouseLoc);
}

int Grid::mouseClick(Point<float> mouseLoc, bool rightClick) {
    for (u64 x = 0; x < cells_.size(); x++) {
        for (u64 y = 0; y < cells_[x].size(); y++) {
            auto& cell = cells_[x][y];
            if (cell.getCenter().x - cellWidth_ / 2 <= mouseLoc.x &&
                mouseLoc.x <= cell.getCenter().x + cellWidth_ / 2 &&
                cell.getCenter().y - cellHeight_ / 2 <= mouseLoc.y &&
                mouseLoc.y <= cell.getCenter().y + cellHeight_ / 2) {

                if (firstClick_ && !rightClick) {
                    placeBombs(Point<u64> { x, y });
                    setupNeighbors();
                    calculateAllBombNeighbors();
                    firstClick_ = false;
                }
                if (!cell.isVisible()) cell.mouseClick(mouseLoc, rightClick);
                else;// TODO: If mine count satisfied, attempt to open neighbours
                if (!rightClick && cell.isBombCell() && cell.isVisible()) return -1;
            }
        }
    }

    return checkWinCondition();
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
    // mines.clear(); // freed by RAII
    *this = Grid(size_, totalMines_, cellWidth_, cellHeight_);
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