#include "gameboard.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>

#include <QDebug>

GameBoard::GameBoard(QObject *parent, size_t board_dimension)
    : QAbstractListModel{parent}, m_dimension{board_dimension},
      m_boardsize{board_dimension * board_dimension}, m_hiddenElementValue{
                                                          m_boardsize} {
  m_raw_board.resize(m_boardsize);
  std::iota(m_raw_board.begin(), m_raw_board.end(), 1);
  shuffle();
}

namespace {
template <typename T> bool inRange(T low, T high, T x) {
  return (low <= x && x <= high);
}

bool is_adjacent(GameBoard::Position first, GameBoard::Position second) {
  if (first == second) {
    return false;
  }

  const auto calc_distance = [](size_t pos1, size_t pos2) {
    int distance = static_cast<int>(pos1);
    distance -= static_cast<int>(pos2);
    distance = std::abs(distance);
    return distance;
  };

  bool result{false};

  if (first.first == second.first) {
    int distance = calc_distance(first.second, second.second);
    if (distance == 1) {
      result = true;
    }
  } else if (first.second == second.second) {
    int distance = calc_distance(first.first, second.first);
    if (distance == 1) {
      result = true;
    }
  }

  return result;
}
} // namespace

void GameBoard::shuffle() {
  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::mt19937 g(seed);

  do {
    std::shuffle(m_raw_board.begin(), m_raw_board.end(), g);
  } while (!isBoardValid());
  emit dataChanged(createIndex(0, 0),
                   createIndex(static_cast<int>(m_boardsize), 0));
}

bool GameBoard::isBoardValid() const {
  int inv{0};
  for (size_t i{0}; i < m_boardsize; ++i) {
    for (size_t j = 0; j < i; ++j) {
      if (m_raw_board[j].value > m_raw_board[i].value) {
        ++inv;
      }
    }
  }

  const size_t start_point = 1;

  for (size_t i = 0; i < m_boardsize; ++i) {
    if (m_raw_board[i].value == m_boardsize) {
      inv += start_point + i / m_dimension;
    }
  }

  return (inv % 2) == 0;
}

bool GameBoard::isBoardFinished() const {
  bool state{true};
  size_t pos{0};
  std::for_each(m_raw_board.begin(), m_raw_board.end(),
                [&state, &pos](const Tile &t) {
                  if (t.value != ++pos)
                    state = false;
                });
  return state;
}

bool GameBoard::isPositionValid(const size_t position) const {
  return position < m_boardsize;
}

int GameBoard::rowCount(const QModelIndex & /*parent*/) const {
  return static_cast<int>(m_boardsize);
}

QVariant GameBoard::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || role != Qt::DisplayRole) {
    return {};
  }

  const auto index_row{static_cast<size_t>(index.row())};

  if (!isPositionValid(index_row)) {
    return {};
  }

  return QVariant(static_cast<int>(m_raw_board[index_row].value));
}

size_t GameBoard::hiddenElementValue() const { return m_hiddenElementValue; }

GameBoard::Position GameBoard::getRowCol(size_t index) const {
  size_t row = index / m_dimension;
  size_t col = index % m_dimension;

  return std::make_pair(row, col);
}

bool GameBoard::move(int index) {
  if (isBoardFinished()) {
    auto t = gameTimer.remainingTimeAsDuration().count();
    if (t > 0) {
      m_gameTime = static_cast<size_t>(t);
      gameTimer.stop();
    } else
      qDebug() << "Time is: " << t;
    return false;
  }
  if (!isPositionValid(static_cast<size_t>(index))) {
    return false;
  }

  Position positionOfIndex{getRowCol(static_cast<size_t>(index))};

  auto hiddenElementIterator =
      std::find(m_raw_board.begin(), m_raw_board.end(), m_hiddenElementValue);

  Q_ASSERT(hiddenElementIterator != m_raw_board.end());
  Position hiddenElementPosition{getRowCol(static_cast<size_t>(
      std::distance(m_raw_board.begin(), hiddenElementIterator)))};

  if (!is_adjacent(positionOfIndex, hiddenElementPosition)) {
    qDebug() << "Fail: " << __PRETTY_FUNCTION__ << " at index:" << index;
    return false;
  }
  int distanceToHiddenElement{static_cast<int>(
      std::distance(m_raw_board.begin(), hiddenElementIterator))};

  int destination = index > distanceToHiddenElement
                        ? distanceToHiddenElement
                        : distanceToHiddenElement + 1;

  // Really swap index and dTHE but for QAbstractListModel move index and
  // destination
  if (beginMoveRows(QModelIndex(), index, index, QModelIndex(), destination)) {
    if (!gameTimer.isActive())
      gameTimer.start();

    std::swap(m_raw_board.at(static_cast<size_t>(index)),
              m_raw_board.at(static_cast<size_t>(distanceToHiddenElement)));
    endMoveRows();

    setStepsCounter(++m_stepsCounter);
    qDebug() << "Done: " << __PRETTY_FUNCTION__ << " at index:" << index
             << " score: " << stepsCount();

    emit dataChanged(createIndex(0, 0),
                     createIndex(static_cast<int>(m_boardsize), 0));
  }

  return true;
}

int GameBoard::stepsCount() { return m_stepsCounter; }

void GameBoard::setStepsCounter(int stepsCounter) {
  m_stepsCounter = stepsCounter;
  emit stepsCountChanged(stepsCounter);
}
