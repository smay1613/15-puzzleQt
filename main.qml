import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("15-puzzle")

    Component.onCompleted: {
        _toolBar.restartClicked.connect(_gameBoard.newgame)
        _toolBar.secretClicked.connect(_gameBoard.finish)
        _toolBar.secretClicked.connect(_Victory.gameFinished)

        _Victory.restartClicked.connect(_gameBoard.newgame)

        _gameBoard.gameStateChanged.connect(_Victory.gameStateChanged)
    }

    GameBoard {
        id: _gameBoard
        function finish() {
            model.finishBoard()
            console.log("Board completed")
        }
        function newgame() {
            model.shuffle()
            setState(true)
            console.log("New game was started")
        }

        anchors.top: _toolBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5
        visible: true
        enabled: true
    }
    ToolBar {
        id: _toolBar
        scoreValue: _gameBoard.model.stepsCount
    }
    VictoryScreen {
        id: _Victory

        anchors.fill: _gameBoard
        visible: false
        enabled: false
    }
}
