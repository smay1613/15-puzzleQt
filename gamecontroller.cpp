#include "gamecontroller.h"

GameController::GameController(QObject *parent) : QObject(parent)
{
    connect(&gameBoard, &GameBoard::tileMoved, this, &GameController::tileMoved);
}

GameBoard* GameController::getModel()
{
    return &gameBoard;
}
