#include "movecounter.h"
#include <QSettings>

MoveCounter::MoveCounter(QObject *parent)
    : QObject(parent)
{

}

int MoveCounter::currentCount() const
{
    return currentCount_;
}

void MoveCounter::increment()
{
    emit currentCountChanged(++currentCount_);
}

void MoveCounter::resetCurrentCount()
{
    if (currentCount_ != 0) {
        emit currentCountChanged(currentCount_ = 0);
    }
}

int MoveCounter::bestScore() const
{
    return QSettings().value("bestScore", -1).toInt();
}

void MoveCounter::updateBestScore()
{
    const int currentBestScore = bestScore();
    if (currentBestScore <= currentCount_ && currentBestScore != -1) {
        return;
    }

    QSettings().setValue("bestScore", currentCount_);
    emit bestScoreChanged(currentCount_);
}
