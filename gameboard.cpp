#include "gameboard.h"

#include <cmath>
#include <numeric>
#include <algorithm>
#include <random>
#include <QDebug>

GameBoard::GameBoard(QObject *parent, size_t board_dimension):
    QAbstractListModel {parent},
    m_dimension {board_dimension},
    m_boardsize {board_dimension * board_dimension},
    m_hiddenElementValue {m_boardsize}
{
    m_raw_board.resize(m_boardsize);
    std::iota(m_raw_board.begin(), m_raw_board.end(), 1);
    shuffle();
}

void GameBoard::shuffle()
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 g(seed);

    do {
        std::shuffle(m_raw_board.begin(), m_raw_board.end(), g);
    }
    while (!isBoardValid());
}

bool GameBoard::isBoardValid() const
{
    int inv {0};
    for (size_t i {0}; i < m_boardsize; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (m_raw_board[j].value > m_raw_board[i].value){
                ++inv;
            }
        }
    }

    const size_t start_point = 1;

    for (size_t i = 0; i < m_boardsize; ++i) {
        if (m_raw_board[i].value == m_boardsize){
            inv += start_point + i / m_dimension;
        }
    }

    return (inv % 2) == 0;
}

bool GameBoard::isPositionValid(const size_t position) const
{
    return position < m_boardsize;
}

int GameBoard::hiddenElementIndex() const
{
    const auto hiddenElementIterator =
            std::find(m_raw_board.begin(), m_raw_board.end(),
                      m_hiddenElementValue);

    return static_cast<int>(std::distance(m_raw_board.begin(), hiddenElementIterator));
}

int GameBoard::rowCount(const QModelIndex &/*parent*/) const
{
    return static_cast<int>(m_boardsize);
}

QVariant GameBoard::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }

    const auto index_row {static_cast<size_t>(index.row())};

    if (!isPositionValid(index_row)) {
        return {};
    }

    return QVariant(static_cast<int>(m_raw_board[index_row].value));
}

size_t GameBoard::hiddenElementValue() const
{
    return m_hiddenElementValue;
}

GameBoard::Position GameBoard::getRowCol(size_t index) const
{
    size_t row = index / m_dimension;
    size_t col = index % m_dimension;

    return std::make_pair(row, col);
}

namespace  {
    bool is_adjacent (GameBoard::Position first, GameBoard::Position second)
    {
        if (first == second){
            return false;
        }

        const auto calc_distance = [](size_t pos1, size_t pos2){
            int distance = static_cast<int>(pos1);
            distance -= static_cast<int>(pos2);
            distance = std::abs(distance);
            return distance;
        };

        bool result {false};

        if (first.first == second.first) {
            int distance = calc_distance (first.second, second.second);
            if (distance == 1) {
                result = true;
            }
        } else if (first.second == second.second) {
            int distance = calc_distance (first.first, second.first);
            if (distance == 1) {
                result = true;
            }
        }

        return result;
    }
}

bool GameBoard::move(int index)
{
    if (!isPositionValid(static_cast<size_t>(index))) {
        return false;
    }

    Position positionOfIndex {getRowCol(index)};
    const int oldHiddenIndex = hiddenElementIndex();
    Position hiddenElementPosition {getRowCol(oldHiddenIndex)};

    if (!is_adjacent(positionOfIndex, hiddenElementPosition)) {
        return false;
    }

    moveRow(QModelIndex(), index, QModelIndex(), index > oldHiddenIndex ? oldHiddenIndex : oldHiddenIndex + 1);

    const int newHiddenIndex = hiddenElementIndex();
    if (newHiddenIndex != index) {
        moveRow(QModelIndex(), newHiddenIndex, QModelIndex(), newHiddenIndex > index ? index : index + 1);
    }
    return true;
}

bool GameBoard::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild)
{
    const int sourceEndRow = sourceRow + count;
    const bool nice_input = (sourceEndRow > 0) &&
            (sourceEndRow <= static_cast<int>(m_boardsize)) &&
            !(sourceRow <= destinationChild && destinationChild < sourceEndRow);
    if (!nice_input) {
        qWarning().nospace()
                << "GameBoard::moveRows. Bad input got: sourceRow = " << sourceRow
                << ", count = " << count << ", destinationChild = " << destinationChild;
        return false;
    }

    beginMoveRows(sourceParent, sourceRow, sourceEndRow - 1, destinationParent, destinationChild);
    const std::vector<Tile> movingRowsCopy = {m_raw_board.cbegin() + sourceRow,
                                              m_raw_board.cbegin() + sourceEndRow};
    m_raw_board.erase(m_raw_board.cbegin() + sourceRow,
                      m_raw_board.cbegin() + sourceEndRow);
    m_raw_board.insert(m_raw_board.cbegin() + destinationChild - (destinationChild > sourceRow ? count : 0),
                       movingRowsCopy.begin(), movingRowsCopy.end());

    endMoveRows();
    return true;
}
