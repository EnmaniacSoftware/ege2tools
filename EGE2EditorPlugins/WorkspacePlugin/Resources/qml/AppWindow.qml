import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import EgeControls 1.0

Rectangle {
    MenuBar {
        id: main_window_bar

        anchors.left: parent.left
        anchors.right: parent.right

        Menu {
            title: qsTr("&File")
            Action {
                id: menu_action_file_new
                text: qsTr("&New...")
            }
            Action {
                text: qsTr("&Open...")
            }
            Action {
                text: qsTr("&Save")
            }
            MenuSeparator {}
            Action {
                text: qsTr("&Close")
                enabled: false
            }
            MenuSeparator {}
            Action {
                text: qsTr("&Quit")
            }
        }
    }

    EmptyProject {
        id: emptyproject

        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors.topMargin: 0
        anchors.bottomMargin: 0

        anchors {
            left: parent.left
            right: parent.right
            top: main_window_bar.bottom
            bottom: parent.bottom // statusbar.top
        }
    }

    NewProjectDialog {
        id: new_project_dialog
    }

    StatusBar {
        id: statusbar

        color: palette.dark
        fillColor: palette.window
        height: 20

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }

    Connections {
        target: menu_action_file_new

        function onTriggered() {
            // var component = Qt.createComponent("NewProjectWindow.qml", main_window)
            // var new_project_window = component.createObject(main_window)
            new_project_dialog.open()
        }
    }
}
