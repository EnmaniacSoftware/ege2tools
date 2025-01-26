import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Dialogs

import "qrc:coreplugin/qml/js/Url-utilities.js" as UrlUtils
import "qrc:coreplugin/qml/js/FileSystem-utilities.js" as FSUtils

import EgeControls 1.0

Dialog {
    title: qsTr("New project")
    modal: true

    closePolicy: Popup.CloseOnEscape

    standardButtons: Dialog.Ok | Dialog.Cancel

    width: 420
    height: 400

    anchors.centerIn: parent

    onAccepted: {
        projectFactoryModel.createProject(project_type_listview.currentItem.projectName,
                                          project_name_textfield.text,
                                          dialog_browseLocation.selectedFolder)
    }

    onRejected: console.log("Cancel clicked")

    Component.onCompleted: {
        update_ok_button()
    }

    ColumnLayout {
        id: content

        spacing: 6
        anchors {
            fill: parent
            leftMargin: 6
            rightMargin: 6
            topMargin: 6
            bottomMargin: 6
        }

        Text {
            text: qsTr("Select project type:")
        }

        ListView {
            id: project_type_listview

            Layout.fillWidth: true
            height: 200
            required model
            model: projectFactoryModel

            delegate: ItemDelegate {
                required property string projectName
                required property int index

                font.family: "Arial"
                font.pointSize: 9

                width: project_type_listview.width

                text: projectName
                highlighted: ListView.isCurrentItem

                onClicked: project_type_listview.currentIndex = index
            }
        }

        Text {
            text: qsTr("Project name:")
        }

        TextField {
            id: project_name_textfield
            placeholderText: qsTr("Enter the name of the project")
            Layout.fillWidth: true
        }

        Text {
            text: qsTr("Project location:")
        }

        RowLayout {
            id: rowLayout
            Layout.fillWidth: true

            FolderDialog {
                id: dialog_browseLocation
            }

            TextField {
                id: label_projectLocation
                placeholderText: qsTr("Select project location")
                readOnly: true
                Layout.fillWidth: true
            }

            Button {
                id: button_browseLocation
                text: qsTr("Browse")
            }
        }
    }

    Connections {
        target: project_type_listview

        function onCurrentItemChanged() {
            console.log("list item chaned:", project_type_listview.currentItem.projectName)
        }
    }

    Connections {
        target: dialog_browseLocation

        function onAccepted() {
            label_projectLocation.text = UrlUtils.extract_path_from_url(dialog_browseLocation.selectedFolder)
            update_ok_button()
        }
    }

    Connections {
        target: button_browseLocation

        function onClicked() {
            dialog_browseLocation.open()
        }
    }

    Connections {
        target: project_name_textfield

        function onTextChanged() {
            update_ok_button()
        }
    }

    function update_ok_button() {
        standardButton(Dialog.Ok).enabled = FSUtils.isValidFileName(project_name_textfield.text) && label_projectLocation.text.length !== 0
    }
}
