// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick

Window {
    id: root

    title: qsTr("My App Window")
    visible: true
    width: 1024
    height: 768

    SystemPalette {
        id: palette
        colorGroup: SystemPalette.Active
    }

    AppWindow {
        id: main_window

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
    }
}

