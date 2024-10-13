import QtQuick
import QtQuick.Controls.Universal
import QtQuick.Layouts
import EgeControls 1.0
import QtQuick.Controls 2.15;
import QtQuick.Controls.Fusion

Window {
    id: window
    visible: true
    width: 1024
    height: 768
    Universal.theme: Universal.System
    color: palette.window
    title: qsTr("My App Window")

    SystemPalette { id: palette; colorGroup: SystemPalette.Active }

    MenuBar {
        id: main_window_bar
        Layout.fillWidth: true

        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&New...")
                onTriggered: newProject.visible = true
            }

            Action { text: qsTr("&Open...") }
            Action { text: qsTr("&Save") }
            MenuSeparator { }
            Action { text: qsTr("&Close")
                     enabled: false }
            MenuSeparator { }
            Action { text: qsTr("&Quit") }
        }
    }

    EmptyProject {
        id: emptyproject
        anchors {
            left: parent.left
            right: parent.right
            top: main_window_bar.bottom
            bottom: statusbar.top
        }
    }

    StatusBar {
        id: statusbar

        color: palette.dark
        fillColor: palette.light
        height: 20

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }

    property var newProject : Window {
        title: qsTr("New project")
        modality: Qt.ApplicationModal
        flags:  Qt.Dialog

        Universal.theme: Universal.System
        color: palette.window

        // make sure it fit entire content
        width: new_project.implicitWidth
        height: new_project.implicitHeight

        // make window non-resizable
        minimumHeight: height
        maximumHeight: height
        minimumWidth: width
        maximumWidth: width

        NewProject {
           id: new_project
        }
    }
}
