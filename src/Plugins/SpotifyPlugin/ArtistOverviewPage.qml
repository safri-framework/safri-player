import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.0
import QtSpotify 1.0
import "Helpers.js" as Helper

Rectangle
{
    id: main
    property var browse
    property string artist
    property string pictureID
    property string albumName


    color:"transparent"
    visible: Stack.status == Stack.Active
    onBrowseChanged:
    {
        if(p.internalBrowse)
            p.internalBrowse.destroy()
        p.internalBrowse = browse
    }

    QtObject
    {
        id:p
        property var internalBrowse;
    }


    ColumnLayout
    {
        id:layout
        anchors.fill: parent
        spacing:0
//        Rectangle
//        {
//            height: 58
//            Layout.fillWidth: true
//            color: Helper.transparentColor("000000", 10)

//              //  anchors.fill: parent
//                SpotifyImage
//                {
//                    id:cover
//                    height: parent.height
//                    width: height
//                    spotifyId: pictureID
//                }

//                Rectangle
//                {
//                    anchors.left: cover.right
//                    anchors.right: parent.right
//                    height: parent.height
//                    anchors.leftMargin: 10
//                    color:"transparent"

//            }
//        }
        Rectangle
        {
            height: 58
            Layout.fillWidth: true
            color: Helper.transparentColor("000000", 10)

            RowLayout
            {
                anchors.fill: parent

                Rectangle
                {
                    Layout.fillHeight: true
                    width: 30;
                    color: mouseArea_back.containsMouse ? Helper.transparentColor("000000", 10) : "transparent"

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
                        id:mouseArea_back
                        hoverEnabled: true
                        anchors.fill: parent;
                        onClicked: stackView.pop()
                    }
                }

                Item
                {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Text
                    {
                        horizontalAlignment:Text.AlignRight
                        anchors.verticalCenter: parent.verticalCenter
                        id: artistLabel
                        text: artist
                        color:"white"
                        width:parent.width
                        font.pixelSize:  14
                        Component.onCompleted: if(renderType == Text.NativeRendering) console.log("native")
                    }
                }

                Item
                {
                    id: coverWrapper
                    height: parent.height
                    width: height
                    anchors.right: parent.right

                    SpotifyImage
                    {
                        anchors.fill: parent
                        anchors.margins: 5
                        id:cover
                        spotifyId: pictureID
                    }
                }
            }
        }

        AlbumView
        {
            model: p.internalBrowse.albums()
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}


