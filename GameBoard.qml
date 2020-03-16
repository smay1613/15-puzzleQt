import QtQuick 2.0
import Game 1.0
import QtQuick.Dialogs 1.1

GridView {
    id: root

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
                    if ( root.model.isFinished()) {
                        my_message.visible = true;
                    }
                }
            }
        }
    }

    GameController_qml{
        id: _gameController
    }

    Component.onCompleted: {
        root.model =  _gameController.getModel();
    }

    MessageDialog {
        id: my_message
        title: "May I have your attention please"
        text: root.model.getMessage()
        onAccepted: {
            console.log("And of course you could only agree.")
            root.model.restart();
        }
    }

}
