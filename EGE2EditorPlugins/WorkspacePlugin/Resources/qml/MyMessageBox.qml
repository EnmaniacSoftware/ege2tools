import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Popup {
    id: messageBox

    modal: true
    focus: true

    closePolicy: Popup.CloseOnEscape

    property string title: "Message"
    property string message: "This is a message."
    property string iconType: "info" // Accepts: "info", "warning", "error", "question"
    property color titleBarColor: "#2196F3"
    //property alias buttons: buttonRow.children

    width: 350
    height: 200
    padding: 0

    anchors.centerIn: parent

    background: Rectangle {
        color: "white"
        radius: 8
        border.color: "#ccc"
        border.width: 1
    }

     Column {
         width: parent.width
         spacing: 10

        // Title Bar
        // TODO: clip title bar
        Rectangle {
            id: title_bar
            width: parent.width
            height: 30
            color: messageBox.titleBarColor

            Text {
                text: messageBox.title
                font.bold: true
                color: "white"
                verticalAlignment: Text.AlignVCenter
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 5
                anchors.leftMargin: 5
                anchors.verticalCenter: parent.verticalCenter
            }

            Button {
                text: "✖"
                width: 20
                height: 20
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.topMargin: 5
                anchors.rightMargin: 5
                onClicked: messageBox.close()
            }
        }

        // Message Content
        RowLayout {
             width: parent.width
             height: parent.height - title_bar.height

            // anchors.horizontalCenter: parent.horizontalCenter
            // spacing: 10

            Image {
                source: {
                    if (messageBox.iconType === "info") return "qrc:/workspaceplugin/icons/message-box-icon-info.png";
                    if (messageBox.iconType === "warning") return "qrc:/workspaceplugin/icons/message-box-icon-warning.png";
                    if (messageBox.iconType === "error") return "qrc:/workspaceplugin/icons/message-box-icon-error.png";
                    if (messageBox.iconType === "question") return "qrc:/workspaceplugin/icons/message-box-icon-question.png";
                    return "";
                }
                width: 40
                height: 40
                visible: source !== ""
            }

            Text {
                text: messageBox.message
                width: parent.width - 60
                wrapMode: Text.WordWrap
                font.pixelSize: 14
            }
        }

         // Buttons
        DialogButtonBox {
            id: buttonBox

            standardButtons: DialogButtonBox.Ok | DialogButtonBox.Cancel
            // anchors.horizontalCenter: parent.horizontalCenter
            // anchors.bottom: parent.bottom
            // anchors.bottomMargin: 10

            onAccepted: {
                messageBox.buttonClicked(StandardButton.Ok);
                messageBox.close();
            }

            onRejected: {
                messageBox.buttonClicked(StandardButton.Cancel);
                messageBox.close();
            }
        }
     }
}
