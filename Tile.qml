import QtQuick 2.0

Rectangle {
    id: root
    property alias internalText: valueText
    color: "lightgreen"
    border.color: "black"
    border.width: 1
    radius: 5

    Text {
        id: valueText
        text: "1"

        font.bold: true
        font.pointSize: root.height * 0.33

        anchors.centerIn: root
    }
}
