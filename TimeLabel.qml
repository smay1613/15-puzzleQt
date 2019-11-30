import QtQuick 2.0
import QtQuick.Controls 2.5

Label {
    property int seconds: 0
    property double startTime: new Date().getTime()
    text: qsTr("Time: %1").arg(Math.ceil(seconds))

    Timer {
        interval: 50; running: true; repeat: true
        onTriggered: {
            seconds = (new Date().getTime() - startTime) / 1000;
        }
    }
}
