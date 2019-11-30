﻿#pragma once

#include <vector>
#include <QAbstractListModel>

class GameBoard : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int hiddenElementValue READ hiddenElementValue CONSTANT)
public:
    static constexpr size_t DEFAULT_DIMENSION  {4};

    GameBoard(QObject *parent = nullptr, size_t board_dimension = DEFAULT_DIMENSION);

    struct Tile {
        size_t value {};
        Tile& operator= (const size_t new_value){
            value = new_value;
            return *this;
        }
        bool operator==(size_t other) const {
            return other == value;
        }
        bool operator==(const Tile &other) const {
            return other.value == value;
        }
    };

    void shuffle();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    size_t hiddenElementValue() const;

    Q_INVOKABLE bool move (int index);
    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count,
                  const QModelIndex &destinationParent, int destinationChild) override;

    using Position = std::pair<size_t, size_t>;

signals:
    void tileMoved();
    void solved();

private:
    std::vector<Tile> m_raw_board;
    const size_t m_dimension;
    const size_t m_boardsize;

    const size_t m_hiddenElementValue;

    bool isBoardValid() const;
    bool isPositionValid(const size_t position) const;
    bool isSolved() const;

    int hiddenElementIndex() const;

    Position getRowCol(size_t index) const;

};
