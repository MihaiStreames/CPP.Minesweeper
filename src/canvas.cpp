#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "canvas.hpp"
#include "common.hpp"

Canvas::Canvas()
    : grid_(10, 15, 50, 50),
      mineCounterText_("Mines: 0", { 0, 20 }),
      timerText_("Time: 0", { 0, 20 }),
      mineCount_(0),
      startTime_(0),
      gameOver_(false),
      gameWon_(false),
      gameStarted_(false),
      revealingMines_(false),
      mineRevealIndex_(0),
      lastRevealTime_(0) {
    mineCount_ = grid_.getTotalMines();
    mineCounterText_.setString("Mines: " + std::to_string(mineCount_));
    updateTextPositions();
}

void Canvas::updateTextPositions() {
    timerText_.setCenter({ 50, 20 });
    int textWidth = al_get_text_width(font, mineCounterText_.getString().c_str());
    mineCounterText_.setCenter({ static_cast<float>(windowWidth) - 10 - static_cast<float>(textWidth) / 2.0f, 20 });
}

void Canvas::draw() {
    grid_.draw();

    int markedCells = grid_.getMarkedCellsCount();
    int minesLeft = mineCount_ - markedCells;
    mineCounterText_.setString("Mines: " + std::to_string(minesLeft));
    updateTextPositions();
    mineCounterText_.draw();
    timerText_.draw();

    if (revealingMines_) {
        if (mineRevealIndex_ < grid_.mines.size()) {
            double currentTime = al_get_time();
            if (currentTime - lastRevealTime_ >= 0.2) {
                grid_.mines[mineRevealIndex_]->reveal();
                mineRevealIndex_++;
                lastRevealTime_ = currentTime;
            }
        } else {
            revealingMines_ = false;
        }
        // TODO: add revealing erroneous flags
    }

    if (gameOver_ && !revealingMines_) {
        showGameOverMessage();
    }

    if (gameStarted_ && !gameOver_) {
        double elapsedTime = al_get_time() - startTime_;
        timerText_.setString("Time: " + std::to_string(static_cast<int>(elapsedTime)));
    }
}

void Canvas::showGameOverMessage() const {
    ALLEGRO_COLOR overlayColor = al_map_rgba(0, 0, 0, 128);
    al_draw_filled_rectangle(0, 0, static_cast<float>(windowWidth), static_cast<float>(windowHeight), overlayColor);

    float popupWidth = 450.0f;
    float popupHeight = 150.0f;
    float popupX = mid_x - popupWidth / 2;
    float popupY = mid_y - popupHeight / 2;
    ALLEGRO_COLOR popupColor = al_map_rgb(255, 255, 255);
    al_draw_filled_rectangle(popupX, popupY, popupX + popupWidth, popupY + popupHeight, popupColor);
    al_draw_rectangle(popupX, popupY, popupX + popupWidth, popupY + popupHeight, COLOR_BLACK, 2.0);

    std::string message = gameWon_ ? "You Win!" : "Game Over";
    Text gameOverText(message, { mid_x, mid_y - 30 }, COLOR_RED);
    gameOverText.draw();

    Text restartText("Press R to restart or Q to quit", { mid_x, mid_y + 20 }, COLOR_BLACK);
    restartText.draw();
}

void Canvas::mouseMove(Point<float> mouseLoc) {
    if (!gameOver_) {
        grid_.mouseMove(mouseLoc);
    }
}

void Canvas::mouseClick(Point<float> mouseLoc, bool rightClick) {
    if (!gameOver_ && !revealingMines_) {
        int gameState = grid_.mouseClick(mouseLoc, rightClick);
        if (gameState == -1) {
            gameOver_ = true;
            gameStarted_ = false;
            lastRevealTime_ = al_get_time();
            revealingMines_ = true;
            mineRevealIndex_ = 0;
        } else if (gameState == 1) {
            gameOver_ = true;
            gameWon_ = true;
            gameStarted_ = false;
        } else {
            if (!gameStarted_ && !rightClick) {
                gameStarted_ = true;
                startTime_ = al_get_time();
            }
        }
    }
}

void Canvas::keyDown(int keyCode) {
    if (keyCode == ALLEGRO_KEY_R) {
        grid_.reset();
        mineCount_ = grid_.getTotalMines();
        mineCounterText_.setString("Mines: " + std::to_string(mineCount_));
        gameOver_ = false;
        gameWon_ = false;
        gameStarted_ = false;
        revealingMines_ = false;
        mineRevealIndex_ = 0;
        startTime_ = 0;
        timerText_.setString("Time: 0");
    } else if (keyCode == ALLEGRO_KEY_Q) {
        shouldExit = true; // Signal to exit
    }
}