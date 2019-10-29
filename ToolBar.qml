import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    id:root

    property int scoreValue
    property alias newGame: _newGameButton

    signal restartClicked

    Component.onCompleted: {
        _newGameButton.clicked.connect(restartClicked)
    }

    width: parent.width;
    height: parent.height/10;
    anchors.top:parent.top
    Button{
        id:_newGameButton

        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

        text:"Start new game"

    }


    Text{
        id:_score

        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter

        text:scoreValue
    }

    Text {
        id: _scoreText

        anchors.right: _score.left
        anchors.verticalCenter: parent.verticalCenter

        text: "Score: "
    }
}
