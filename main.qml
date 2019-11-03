import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("15-puzzle")



    Component.onCompleted: {
        _toolBar.restartClicked.connect(_gameBoard.restart)
        _toolBar.secretClicked.connect(_gameBoard.finish)
        _toolBar.secretClicked.connect(_Victory.gameFinished)
        _Victory.restartClicked.connect(_gameBoard.newgame)
    }

    GameBoard {
        id: _gameBoard
        function restart(){
            model.shuffle()
            console.log("Game restarted")
        }
        function finish(){
            model.finishBoard()
            console.log("Game finished")

        }
        function newgame(){
            triggerState()
            model.shuffle()
            console.log("New game was started")
        }

        anchors.top: _toolBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5
        visible: false
        enabled: false
    }
    ToolBar{
        id:_toolBar
        scoreValue: _gameBoard.model.stepsCount
    }
    VictoryScreen{
        id:_Victory
        //anchors.top: _gameBoard.top
        //anchors.right: _gameBoard.right
        //anchors.bottom: _gameBoard.bottom
        //anchors.left: _gameBoard.left
        anchors.fill: _gameBoard
        visible: true
        enabled: true
    }





}
