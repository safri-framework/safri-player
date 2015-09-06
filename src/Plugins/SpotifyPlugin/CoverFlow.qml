import QtQuick 2.2
import "Helpers.js" as Helpers

ListView
{



    id:root
    orientation: ListView.Horizontal
    highlightFollowsCurrentItem: false
    property int selectedIndex: 0
    onSelectedIndexChanged: gotoIndex(selectedIndex)
    onModelChanged: selectedIndex = 0


    QtObject
    {
        id:p
        property int centerIndex: indexAt(root.width/2, root.height/2)
    }

    delegate:
    PictureItemDelegate
    {
        opacity: index == selectedIndex ? 1 : 0.6
        spacing: 10
        width:160
        height:160
        anchors.verticalCenter: parent.verticalCenter
        albumSize: index == selectedIndex ? 140:120
        Behavior on albumSize {NumberAnimation{duration: 150}}
        spotifyPictureID: pictureId
        text: name
        onClicked: { stackView.push(
                         {item:artistPage,
                             properties:
                             {
                                 artist: name,
                                 browse: root.model.artistBrowse(index),
                                 pictureID: pictureId,
                             }
                         }
                    )}
    }

    Rectangle
    {
        height: 120
        anchors.verticalCenter: parent.verticalCenter
        visible: selectedIndex != 0
        width: 30
        color:  leftArea.containsMouse ? Helpers.transparentColor("000000",50):"transparent"//Helpers.transparentColor("000000",0)
        anchors.left: parent.left
        Rectangle
        {
            width: 30
            height: 30
            anchors.centerIn: parent
            rotation: 90
            visible: root.icon
            color:"transparent"
            opacity: 1
            Image
            {
                anchors.centerIn: parent
                source: "qrc:/icons/triangleIndication"
            }
        }
        MouseArea
        {
             id: leftArea
             hoverEnabled: true
            anchors.fill: parent
            onClicked: if(selectedIndex-1 >= 0) {selectedIndex = selectedIndex -1}
        }
    }

    Rectangle
    {
        height: 120
        anchors.verticalCenter: parent.verticalCenter
        width: 30
        visible: selectedIndex != count-1 && count > 0
        color:  rightArea.containsMouse ? Helpers.transparentColor("000000",50):"transparent"//Helpers.transparentColor("000000",0)
        anchors.right: parent.right
        Rectangle
        {
            width: 30
            height: 30
            anchors.centerIn: parent
            rotation: -90
            visible: root.icon
            color:"transparent"
            opacity: 1
            Image
            {
                anchors.centerIn: parent
                source: "qrc:/icons/triangleIndication"
            }
        }
        MouseArea
        {
            hoverEnabled: true
            id: rightArea
            anchors.fill: parent
            onClicked: if(selectedIndex+1 < count){ selectedIndex = selectedIndex+1}
        }
    }

    function gotoIndex(idx)
    {
        var pos = root.contentX;
        var destPos;
        root.positionViewAtIndex(idx, ListView.Center);
        destPos = root.contentX;
        anim.from = pos;
        anim.to = destPos;
        anim.running = true;
    }

    NumberAnimation { id: anim; target: root; property: "contentX"; duration: 150 ; onRunningChanged: console.log("runnin")}
}







