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
    property string coverID
    property string albumName


    color:"transparent"
    visible: Stack.status == Stack.Active
    Stack.onStatusChanged: if(Stack.status == Stack.Inactive)browse.destroy()


    ColumnLayout
    {
        id:layout
        anchors.fill: parent
        spacing:0
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
                    Layout.fillHeight: true
                    width: 30;
                    color: mouseArea_back.containsMouse ? Helper.transparentColor("000000", 10) : "transparent"
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

                    Column
                    {
                       anchors.centerIn: parent
                       width: parent.width
                       height: artistLabel.height + albumLabel.height
                        Text
                        {
                            horizontalAlignment:Text.AlignRight
                            id: artistLabel
                            text: artist
                            color:"white"
                            width:parent.width
                            font.pixelSize:  14
                            opacity: 0.6
                            Component.onCompleted: if(renderType == Text.NativeRendering) console.log("native")
                        }
                        Text
                        {
                            id: albumLabel
                            horizontalAlignment:Text.AlignRight
                            wrapMode: Text.WordWrap
                            width:parent.width
                            text: albumName
                            color:"white"
                            font.pixelSize: 16
                            renderType: Text.NativeRendering
                        }
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
                        spotifyId: coverID
                    }
                }
            }
        }
        TrackList
        {
            clip: true
            Layout.fillHeight: true
            showArtist: false
            Layout.fillWidth: true
            model: browse ? browse.tracks() : undefined
        }
    }

}
