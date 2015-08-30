import QtQuick 2.0
import "Helpers.js" as Helpers
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0
Rectangle
{
    id:root
    property alias spotifyPictureID: image.spotifyId
    property int albumSize: 140
    property int spacing: 0
    property string text
    property string jsonContainer

    signal clicked()
    signal appendToPlaylistClicked()

    width: cellWidth
    height: cellHeight
    color:"transparent"


    Rectangle
    {
        id: innerFrame
        anchors.centerIn: parent
        color: Helpers.transparentColor("000000",10)
        width: albumSize
        height: albumSize
        x:spacing
        y:spacing

        Item
        {
            anchors.fill: parent

            MouseArea
            {
                RowLayout
                {
                    width: parent.width
                    height: 40
                    spacing: 0
                    Icon{ icon: icons.play;height: parent.height}
                    Icon{ icon: icons.addtolist;height: parent.height; onClicked: root.appendToPlaylistClicked()}
                    Item{Layout.fillWidth: true}
                    Icon{ icon: icons.star;height: parent.height }
                    visible: mouseArea.containsMouse
                }


                preventStealing: true
                hoverEnabled: true
                anchors.fill: parent
                id: mouseArea
                drag.target: draggable
                onClicked: root.clicked()
                propagateComposedEvents: true
            }


            id: draggable
            Drag.active: mouseArea.drag.active
            Drag.hotSpot.x: 0
            Drag.hotSpot.y: 0
            Drag.onDragStarted:  Drag.mimeData = { "MediaInfoContainer": container }
            Drag.dragType: Drag.Automatic
        }

        Rectangle
        {
            id:imagewrapper
            width: parent.width
            height: albumSize-40
            color:"transparent"
            clip:true

            DropShadow
            {

                id: rectShadow;
                anchors.fill: source
                cached: true;
                horizontalOffset: 0;
                verticalOffset: 0;
                radius: 20.0;
                samples: 16;
                opacity: 0.8
                color: "#000000";
                smooth: true;
                source: imageShadowWrapper;
                visible: mouseArea.containsMouse
            }

            Item
            {
                id: imageShadowWrapper
                y: mouseArea.containsMouse ? 40-rectShadow.radius: -rectShadow.radius
                Behavior on y{NumberAnimation{duration: 150; easing.type: Easing.OutCubic }}
                width: albumSize
                height: albumSize + rectShadow.radius


                SpotifyImage
                {
                    y:rectShadow.radius
                    spotifyId: spotifyPictureID
                    //defaultImage: "qrc:/icons/noCover"
                    fillMode: Image.PreserveAspectCrop
                    id: image
                    width: albumSize
                    height: albumSize
                }
            }
        }

        Rectangle
        {
            clip:true
            width: parent.width
            height: 40
            anchors.bottom: parent.bottom
            color:Helpers.transparentColor("000000",10)

//            SpotifyImage
//            {
//                spotifyId: spotifyPictureID
//                //defaultImage: "qrc:/icons/noCover"
//                id: effectImage
//                anchors.bottom: parent.bottom
//                width: albumSize
//                height: albumSize
//            }

//            BrightnessContrast
//            {

//                source: parent
//                anchors.fill: parent
//                brightness: -0.4
//            }
            Text
            {
                anchors.fill:  parent
                anchors.rightMargin: 5
                anchors.leftMargin: 5
                anchors.topMargin: 2
                font.pixelSize: 12
                wrapMode: Text.WordWrap
                color: "white"
                id: test
                text: name
                elide: Text.ElideRight
                maximumLineCount: 2
            }
        }

    }
}