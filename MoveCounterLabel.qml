import QtQuick 2.0
import Game 1.0
import QtQuick.Controls 2.5

Label {
    text: qsTr("Moves: %1").arg(_moveCounter.currentCount)
    function increment() {
        _moveCounter.increment()
    }

    MoveCounter_qml {
        id: _moveCounter
    }

}
