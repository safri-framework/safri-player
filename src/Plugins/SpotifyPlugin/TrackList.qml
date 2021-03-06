import QtQuick 2.2
import QtQuick.Layouts 1.1

import "Helpers.js" as Helpers

ListView
{
    id:root
    property bool showArtist: true
    Layout.fillWidth: true
    delegate:
    Rectangle
    {

    MouseArea
    {
        hoverEnabled: true
        anchors.fill: parent
        id: mouseArea
        drag.target: draggable
        onClicked: root.clicked()
    }

    Item
    {
        anchors.fill: parent
        id: draggable
        Drag.active: mouseArea.drag.active
        Drag.hotSpot.x: 0
        Drag.hotSpot.y: 0
        Drag.mimeData: { "MediaInfoContainer": container  }
        Drag.dragType: Drag.Automatic
    }

        width: root.width
        height: 30
        color: (index % 2) == 0 ? "transparent" : Helpers.transparentColor("000000", 10)
        Text
        {
            id:tracknameLabel
            color: "white"
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            elide: Text.ElideRight
            width: parent.width - 40
            anchors.leftMargin: 5
            text: if(root.showArtist)
                      return trackName +" - <font color=\"#bcc1c4\">"+artists+"</font>"
                    else
                      return trackName
            font.pixelSize: 12
            renderType: Text.NativeRendering
            smooth: true
        }

        Text
        {
            color: "white"
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 5
            text:  trackDuration
            font.pixelSize: 12
        }
    }
}
