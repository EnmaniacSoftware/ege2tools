import QtQuick
import QtQuick.Layouts 2.15
import QtQuick.Controls.Fusion

Item {
    id: container

    anchors {
        left: parent.left
        right: parent.right
        top: parent.top
        bottom: parent.bottom
    }

    Text {
        id: label
        opacity: 0.5
        text: qsTr("No open project")

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
        font.pointSize: 20

        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
    }
}
