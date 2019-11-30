import QtQuick 2.0
import QtQuick.Controls 2.5

Label {
    property int seconds: 0
    property double startTime: new Date().getTime()

    function stopTimer() {
        _timer.stop();
    }

    function reset() {
        seconds = 0;
        startTime = new Date().getTime();
        _timer.start();
    }

    text: qsTr("Time: %1").arg(Math.ceil(seconds))

    Timer {
        id: _timer;
        interval: 50; running: true; repeat: true
        onTriggered: {
            seconds = (new Date().getTime() - startTime) / 1000;
        }
    }
}
