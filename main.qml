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
        anchors.bottomMargin: parent.height - _timeLabel.y
    }

    TimeLabel {
        id: _timeLabel
        anchors {
            left: parent.left
            bottom: parent.bottom
            margins: 5
            leftMargin: 10
        }
        font {
            pointSize: parent.height / 4 * 0.15;
            bold: true
        }
    }
}
