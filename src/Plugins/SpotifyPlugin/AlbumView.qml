import QtQuick 2.3
import QtSpotify 1.0
import QtQuick.Controls 1.0
import "Helpers.js" as Helpers



GridView
{

    id:root
    clip:true
    cellHeight: p.albumSize + 2*p.spacing
    cellWidth: cellHeight
    signal clicked(var item)
    add: Transition {
        PropertyAnimation { properties: "opacity"; from: 0; to: 1; duration: 400 }
    }
    remove: Transition {
            PropertyAnimation { properties: "opacity"; from: 1; to: 0; duration: 400 }
        }

     move: Transition {
         NumberAnimation { properties: "x,y"; duration: 1000 }
     }

    boundsBehavior: Flickable.DragOverBounds
    QtObject
    {
       id: p
        property int minAlbumHeight: 120
        property int albumSize:
        {
            var minCount = parseInt(parent.width / (minAlbumHeight + 2*spacing))
            var rest = parent.width % (minAlbumHeight + 2*spacing)
            return minAlbumHeight + parseInt(rest/minCount)
        }
        property int spacing: 10
    }


    delegate:
    PictureItemDelegate
    {
        spotifyPictureID: coverId
        text: name
        albumSize: p.albumSize
        spacing: p.spacing
        jsonContainer: container
        onClicked: { stackView.push(
                         {item:albumPage,
                             properties:
                             {
                                 artist: artist,
                                 browse: root.model.albumBrowse(index),
                                 coverID: coverId,
                                 albumName: name
                             }
                         }
                    )}
        onHoveredChanged: jsonContainer = container
        onAppendToPlaylistClicked: root.model.appendToCurrentPlaylist(index)
        onPlayClicked: root.model.play(index)
    }
}


