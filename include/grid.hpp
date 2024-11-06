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
    bool firstClick_;
    void placeBombs(Point<long unsigned int> first);
    void setupNeighbors();
    void calculateAllBombNeighbors();

public:
    Grid(int gridSize, int minesCount, float cellW, float cellH);
    void draw();
    void mouseMove(Point<float> mouseLoc);
    int mouseClick(Point<float> mouseLoc, bool rightClick);
    int getTotalMines() const;
    int getMarkedCellsCount() const;
    void reset();
    bool checkWinCondition();

    std::vector<Cell*> mines; // For animated mine reveal
};

#endif // GRID_HPP