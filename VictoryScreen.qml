import QtQuick 2.0

Item {
    Rectangle{
        id:root
        width: parent/2
        height: parent/2

        color: "red"
        border.color: "black"
        border.width: 1
        radius: 5
        Text {
            id: _victoryText
            text: qsTr("Game was finished")

            font.bold: true
            font.pointSize: root.height/2

            anchors.centerIn: root
        }
    }
}
