import QtQuick 2.3

Image
{
    property string spotifyId: ""
    property string defaultImage: ""

    source: spotifyId.length > 0 ? ("image://spotify/" + spotifyId) : defaultImage
    asynchronous: true

}
