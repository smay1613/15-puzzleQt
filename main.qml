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

        anchors.top: _toolBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5
    }
    ToolBar{
        id:_toolBar
        scoreValue: _gameBoard.model.stepsCount
    }





}
