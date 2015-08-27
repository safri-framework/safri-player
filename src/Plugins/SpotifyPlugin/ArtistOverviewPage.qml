import QtQuick 2.0
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
                    spotifyId: pictureID
                }

                Rectangle
                {
                    anchors.left: cover.right
                    anchors.right: parent.right
                    height: parent.height
                    anchors.leftMargin: 10
                    color:"transparent"

                    Text
                    {
                        id: albumLabel
                        wrapMode: Text.WordWrap
                        width:parent.width
                        text: artist
                        color:"white"
                        font.pixelSize: 16
                        renderType: Text.NativeRendering
                        anchors.centerIn: parent
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
