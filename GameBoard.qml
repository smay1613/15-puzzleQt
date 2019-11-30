import QtQuick 2.0
import Game 1.0

GridView {
    id: root

    move: Transition {
        NumberAnimation { properties: "x,y"; duration: 1000 }
    }

    cellHeight: height / 4
    cellWidth: width / 4

    interactive: false

    delegate: Item {
        id: _backgroundDelegate
        width: root.cellWidth
        height: root.cellHeight

        visible: root.model.hiddenElementValue !== display

        Tile {
            anchors.fill: _backgroundDelegate
            anchors.margins: 5

            internalText.text: display.toString()

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.model.move(index)
                }
            }
        }
    }

    function restartGame() {
        _gameController.restartGame()
    }

    signal tileMoved()
    signal solved()
    GameController_qml{
        id: _gameController
        onTileMoved: root.tileMoved()
        onSolved: root.solved()
    }

    Component.onCompleted: {
        root.model = _gameController.getModel();
    }
}
