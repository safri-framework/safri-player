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

    Rectangle{color: green; width: 20; height: 20; MouseArea{anchors.fill: parent;onClicked: stackView.pop()}}
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

              //  anchors.fill: parent
                SpotifyImage
                {
                    id:cover
                    height: parent.height
                    width: height
                    spotifyId: coverID
                }

                Rectangle
                {
                    anchors.left: cover.right
                    anchors.right: parent.right
                    height: parent.height
                    anchors.leftMargin: 10
                    color:"transparent"
                    Column
                    {
                       anchors.centerIn: parent
                       width: parent.width
                       height: artistLabel.height + albumLabel.height
                        Text
                        {
                            id: artistLabel
                            text: artist
                            color:"white"
                            font.pixelSize:  14
                            opacity: 0.6
                            Component.onCompleted: if(renderType == Text.NativeRendering) console.log("native")
                        }
                        Text
                        {
                            id: albumLabel
                            wrapMode: Text.WordWrap
                            width:parent.width
                            text: albumName
                            color:"white"
                            font.pixelSize: 16
                            renderType: Text.NativeRendering
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
