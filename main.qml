import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("15-puzzle")

    GameBoard {
        id: _gameBoard
        anchors.fill: parent
        anchors.margins: 5
    }
}
