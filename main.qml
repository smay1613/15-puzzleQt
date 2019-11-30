import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Dialogs 1.2

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
        onTileMoved: _moveCounterLabel.increment()
        onSolved: {
            _moveCounterLabel.updateBestScore();
            _solvedDialog.open();
        }
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
            pointSize: parent.height / 4 * 0.15
            bold: true
        }
    }

    MoveCounterLabel {
        id: _moveCounterLabel
        anchors {
            right: parent.right
            bottom: parent.bottom
            margins: 5
            rightMargin: 10
        }

        font {
            pointSize: parent.height / 4 * 0.15
            bold: true
        }
    }

    MessageDialog {
        property bool lastAnswerIsYes: false
        id: _solvedDialog
        title: qsTr("Solved!")
        text: qsTr("Would u like to restart the game?")
        standardButtons: StandardButton.Yes | StandardButton.No
        icon: StandardIcon.Question
        onYes: {
            lastAnswerIsYes = true;
            _gameBoard.restartGame();
            _moveCounterLabel.resetCurrentCount();
        }
        onNo: Qt.quit()
        // onRejected почему-то не отрабатывает при закрытии диалога
    }

}
