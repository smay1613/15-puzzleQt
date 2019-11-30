#include "movecounter.h"

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
