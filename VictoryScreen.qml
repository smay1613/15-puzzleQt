import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    id: root
    signal restartClicked
    signal gameFinished
    signal gameStateChanged(bool state)

    //  width: parent/2
    // height: parent/2
    // color: "black"
    border.color: "black"
    border.width: 1
    radius: 5

    enabled: false
    visible: false
    Component.onCompleted: {
        _newGameButton.clicked.connect(restartClicked)
        root.gameFinished.connect(viewResult)

        root.gameStateChanged.connect(setState)
    }

    function viewResult() {
        root.enabled = true
        root.visible = true
    }

    function setState(state) {
        root.visible = state
        root.enabled = state
    }

    Text {
        id: _victoryText
        text: qsTr("Game over. You win.")
        // Time and steps counter should be added on victory screen
        font.bold: true
        font.pointSize: height / 4

        height: root.height / 4
        width: root.width / 4

        anchors.left: root.left
        anchors.right: root.right
        anchors.top: root.top

        // anchors.leftMargin: width / 10
        // anchors.rightMargin: width / 10
        //anchors.c
    }
    Button {
        id: _newGameButton
        //anchors.top:_victoryText.bottom
        anchors.centerIn: root

        onClicked: {
            //triggerState()
            setState(false)
        }
        background: Rectangle {
            implicitWidth: root.width / 5
            implicitHeight: root.height / 10
            opacity: enabled ? 1 : 0.3
            border.color: _newGameButton.down ? "#17a81a" : "#21be2b"
            border.width: 1
            radius: 10
        }

        contentItem: Text {
            text: qsTr("Start new game?")
            font: _newGameButton.font
            opacity: enabled ? 1.0 : 0.3
            color: _newGameButton.down ? "#17a81a" : "#21be2b"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
    }
}
