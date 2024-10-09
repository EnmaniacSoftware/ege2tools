import QtQuick
import QtQuick.Controls.Universal
import QtQuick.Layouts
import EgeControls 1.0
import QtQuick.Controls 2.15;

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
     //   font.pointSize: 15

        Menu {
            title: qsTr("&File")
            Action { text: qsTr("&New...") }
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
    }

    StatusBar {
        id: statusbar
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
        color: palette.dark
        fillColor: palette.light
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
