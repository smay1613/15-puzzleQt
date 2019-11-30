#include "gamecontroller.h"

GameController::GameController(QObject *parent) : QObject(parent)
{
    connect(&gameBoard, &GameBoard::tileMoved, this, &GameController::tileMoved);
    connect(&gameBoard, &GameBoard::solved, this, &GameController::solved);
}

GameBoard* GameController::getModel()
{
    return &gameBoard;
}

void GameController::restartGame()
{
    gameBoard.shuffle();
}
