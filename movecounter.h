#pragma once

#include <QObject>

class MoveCounter: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentCount READ currentCount NOTIFY currentCountChanged)

public:
    explicit MoveCounter(QObject *parent = nullptr);

    int currentCount() const;
    Q_INVOKABLE void increment();

signals:
    void currentCountChanged(int);

private:
    int currentCount_ = 0;
};
