#pragma once

#include <QObject>
#include "gameboard.h"

class GameController : public QObject
{
    Q_OBJECT

public:
    explicit GameController(QObject *parent = nullptr);

    Q_INVOKABLE GameBoard* getModel();

private:
    GameBoard gameBoard;
};

