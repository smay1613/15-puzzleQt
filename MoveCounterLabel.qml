import QtQuick 2.0
import Game 1.0
import QtQuick.Controls 2.5

Label {
    property string bestScoreStr: _moveCounter.bestScore === -1 ? "-" : _moveCounter.bestScore;
    text: qsTr("Moves: %1 | Best: %2").arg(_moveCounter.currentCount).arg(bestScoreStr)

    function increment() {
        _moveCounter.increment()
    }

    function updateBestScore() {
        _moveCounter.updateBestScore()
    }

    MoveCounter_qml {
        id: _moveCounter
    }

}
