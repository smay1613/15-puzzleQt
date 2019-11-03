import QtQuick 2.0
import QtQuick.Controls 2.12





    Rectangle{
        id:root
        signal restartClicked
        signal gameFinished
      //  width: parent/2
       // height: parent/2


        color: "red"
        border.color: "black"
        border.width: 1
        radius: 5

        enabled: false
        visible: false
        Component.onCompleted: {
            _restartButton.clicked.connect(restartClicked)
            root.gameFinished.connect(viewResult)
        }

        function viewResult(){
            root.enabled=true
            root.visible=true
        }
        function triggerState(){
            if ((root.enabled==true) &&(root.visible==true))
            {
                root.visible=false
                root.enabled=false
            }
            else
                if ((root.enabled==false) &&(root.visible==false))
                {
                    root.visible=true
                    root.enabled=true
                }

        }

        Item {
            id: _contentText
        }
        Text {
            id: _victoryText
            text: qsTr("Game was finished")
            // Time and steps counter should be added on victory screen
            font.bold: true
            font.pointSize: height/4

            height: root.height/4
            width: root.width/4


            anchors.left: root.left
            anchors.right: root.right
            anchors.top: root.top


            anchors.leftMargin: width/10
            anchors.rightMargin:width/10
            //anchors.c
        }
        Button{
            id:_restartButton
            //anchors.top:_victoryText.bottom
            anchors.centerIn: root

            onClicked: {
                triggerState()
            }
            background: Rectangle {
                implicitWidth: root.width/5
                implicitHeight: root.height/10
                opacity: enabled ? 1 : 0.3
                border.color: _restartButton.down ? "#17a81a" : "#21be2b"
                border.width: 1
                radius: 10
            }


            contentItem: Text {
                text: qsTr("Start new game?")
                font: _restartButton.font
                opacity: enabled ? 1.0 : 0.3
                color: _restartButton.down ? "#17a81a" : "#21be2b"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

        }
    }

