#pragma once

#include <QObject>

class MoveCounter: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentCount
               READ currentCount
               RESET resetCurrentCount
               NOTIFY currentCountChanged)

public:
    explicit MoveCounter(QObject *parent = nullptr);

    int currentCount() const;
    Q_INVOKABLE void increment();
    Q_INVOKABLE void resetCurrentCount();

signals:
    void currentCountChanged(int);

private:
    int currentCount_ = 0;
};
