import QtQuick 2.2

import QtQuick.Layouts 1.0
import QtQuick.Controls 1.2

Rectangle
{
    id: main

    anchors.fill:parent
    width: 400
    height: 600

    color:"transparent"
    Image
    {
        id: name
        source: "qrc:/border_images/background"
        anchors.fill: parent
        fillMode: Image.Tile

    }


      //  Icon{icon: "";id: icon}



    SearchPage{id: searchPage}
   // Test{id:test}


    AlbumOverviewPage{id: albumPage}
    ArtistOverviewPage{id: artistPage}

    Component.onCompleted: stackView.push(searchPage)
    StackView
    {
        anchors.fill: parent
        id: stackView
    }

}
