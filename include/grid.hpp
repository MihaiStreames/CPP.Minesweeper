#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

#include "cell.hpp"

class Grid {
    int size_;
    float cellWidth_;
    float cellHeight_;
    std::vector<std::vector<Cell>> cells_;
    int totalMines_;
    void placeBombs();
    void setupNeighbors();
    void calculateAllBombNeighbors();

public:
    Grid(int gridSize, float cellW, float cellH);
    void draw();
    void mouseMove(Point mouseLoc);
    int mouseClick(Point mouseLoc, bool rightClick);
    int getTotalMines() const;
    int getMarkedCellsCount() const;
    void reset();
    bool checkWinCondition();

    std::vector<Cell*> mines; // For animated mine reveal
};

#endif // GRID_HPP