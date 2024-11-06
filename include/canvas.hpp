#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "grid.hpp"
#include "text.hpp"

class Canvas {
    Grid grid_;
    Text mineCounterText_;
    Text timerText_;
    int mineCount_;
    double startTime_;

    bool gameOver_;
    bool gameWon_;
    bool gameStarted_;

    bool revealingMines_;
    size_t mineRevealIndex_;
    double lastRevealTime_;

public:
    bool shouldExit = false; // Cleanup issues
    Canvas();

    void draw();
    void mouseMove(Point<float> mouseLoc);
    void mouseClick(Point<float> mouseLoc, bool rightClick);
    void keyDown(int keyCode);

private:
    void updateTextPositions();
    void showGameOverMessage() const;
};

#endif // CANVAS_HPP