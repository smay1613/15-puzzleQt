#include "gamecontroller.h"

GameController::GameController(QObject *parent) : QObject(parent)
{
}

GameBoard* GameController::getModel()
{
    return &gameBoard;
}
