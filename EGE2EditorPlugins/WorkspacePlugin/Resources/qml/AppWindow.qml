import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Dialogs

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
                id: menu_action_file_close
                text: qsTr("&Close")
//                enabled: false
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

    MyMessageBox {
        id: myMessageBox
        title: "Warning"
        titleBarColor: "orange"
        message: "Are you sure you want to continue?"
        iconType: "warning"

        // buttons: [
        //     Button {
        //         text: "OK"
        //         onClicked: {
        //             console.log("OK clicked");
        //             myMessageBox.close();
        //         }
        //     },
        //     Button {
        //         text: "Cancel"
        //         onClicked: myMessageBox.close()
        //     }
        // ]
    }

    // MessageDialog {
    //     id: project_close_prompt_dialog

    //     title: qsTr("Project not saved")
    //     text: qsTr("Project contains changes which have not been saved yet!\n\nDo you want to close anyway ?")
    //     buttons: MessageDialog.Ok | MessageDialog.Cancel

    //     modality: Qt.ApplicationModal

    //     closePolicy: Popup.CloseOnEscape

    //     onAccepted: {
    //         console.log("And of course you could only agree.")
    //     }
    //    // Component.onCompleted: visible = true
    // }


    Connections {
        target: menu_action_file_new

        function onTriggered() {
            // var component = Qt.createComponent("NewProjectWindow.qml", main_window)
            // var new_project_window = component.createObject(main_window)
            new_project_dialog.open()
        }
    }

    Connections {
        target: menu_action_file_close

        function onTriggered() {
            console.log("File->Close called")
            myMessageBox.open()
//            project_close_prompt_dialog.warning(qsTr("Project not saved"), qsTr("Project contains changes which have not been saved yet!\n\nDo you want to close anyway ?"))
        }
    }

    Connections {
        target: native_projectFactory

        function onProjectCreated(project) {
            // hide EmptyProject
            emptyproject.visible = false

            // update menu
            menu_action_file_close.enabled = true
        }
    }

    Connections {
        target: native_mainWindow

        function onSetWindowTitle(title) {
            root.title = title
        }
    }
}
