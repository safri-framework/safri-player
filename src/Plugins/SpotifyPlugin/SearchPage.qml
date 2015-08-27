import QtQuick 2.0
import "Helpers.js" as Helpers
import QtQuick.Layouts 1.1
import QtSpotify 1.0
import QtQuick.Controls 1.0

Rectangle
{
    color:"transparent"
    visible: Stack.status == Stack.Active
    SpotifySearch
    {
        id:search
    }

    SearchEdit
    {
        id:searchField
        width:parent.width
        height:30
        Layout.minimumHeight:30
        Layout.maximumHeight: 30
        onTextChanged: {search.query = text; search.search()}
    }

    ColumnLayout
    {
        anchors.top: searchField.bottom
        anchors.bottom: parent.bottom
        width: parent.width

        ExpandableContainer
        {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color:"transparent" //Helpers.transparentColor("000000",10)
            Expandable
            {
                id: artistEx
                text:  "Artist"
                icon: "qrc:/icons/artist"
                expandedHeight: 210
                fixHeight: true
                CoverFlow
                {
                    id:artistFlow
                    model:search.artists()
                    width:main.width
                    Layout.fillWidth: true
                    height:180
                }
            }

            Expandable
            {
               id: albumEx
               text: "Albums"
               icon: "qrc:/icons/album"

               AlbumView
               {
                   id:albumView
                   width: parent.width
                   Layout.fillWidth: true
                   Layout.fillHeight: true
                   model: search.albums()
               }

            }
            Expandable
            {
                id: trackEx
                text: "Tracks"
                icon: "qrc:/icons/song"
                TrackList
                {
                      id:trackView
                      Layout.fillHeight: true
                      Layout.fillWidth: true
                      model: search.trackResults()
                }
           }
        }
    }
}
