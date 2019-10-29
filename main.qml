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

    }

    GameBoard {
        id: _gameBoard
        function restart(){
            model.shuffle()
            console.log("Game restarted")
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
