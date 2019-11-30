#pragma once

#include <QObject>

class MoveCounter: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentCount
               READ currentCount
               RESET resetCurrentCount
               NOTIFY currentCountChanged)
    Q_PROPERTY(int bestScore
               READ bestScore
               NOTIFY bestScoreChanged)

public:
    explicit MoveCounter(QObject *parent = nullptr);

    int currentCount() const;
    Q_INVOKABLE void increment();
    Q_INVOKABLE void resetCurrentCount();

    int bestScore() const;
    Q_INVOKABLE void updateBestScore();

signals:
    void currentCountChanged(int);
    void bestScoreChanged(int);

private:
    int currentCount_ = 0;
};
