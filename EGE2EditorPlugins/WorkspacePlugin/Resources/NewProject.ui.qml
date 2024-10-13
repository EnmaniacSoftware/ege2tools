

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Fusion

Column {
    spacing: 8

    Text {
        text: qsTr("Select project type:")
    }

    ListView {
        id: listView
        width: 484
        height: 234
        model: ListModel {
            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "White"
                colorCode: "white"
            }
        }
    }

    Text {
        text: qsTr("Project name:")
    }

    Text {
        text: qsTr("Project location:")
    }

    TextEdit {
        id: textEdit_projectName
        x: 8
        y: 309
        width: 292
        height: 20
        text: qsTr("Text Edit")
    }

    TextEdit {
        id: textEdit_projectLocation
        x: 8
        y: 379
        width: 349
        height: 20
        text: qsTr("Text Edit")
    }

    Button {
        id: button_browseLocation
        x: 392
        y: 364
        text: qsTr("Browse")
    }

    DialogButtonBox {
        id: button_box
        standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel
    }
}
