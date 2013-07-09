import QtQuick 2.0

Rectangle {

    width: view.width
    height: view.height
    color: "#272727"
    id:view2

    Rectangle
    {

        width: view.width - 20  * root.globalScaleFactor
        height: view.height - 20 * root.globalScaleFactor
        radius: 10 * root.globalScaleFactor
        x:10 * root.globalScaleFactor;
        y:10 * root.globalScaleFactor;
        color:"#1B1B1B"

        Rectangle
        {
         id: currentSongDisplay
         objectName: "currentSongDisplay";
         height: 133 * root.globalScaleFactor
         width: parent.width
         color:"transparent"
         clip: true
         property string songName;
         property string artistName;
         property string albumName;
         property string coverURL;

         function newSong(name, artist, album, cover)
         {
             songName = name;
             artistName = artist;
             albumName = album;
             coverURL = cover;
         }


         BorderImage
         {
             id: name
             source: "resources/labelbackground.png"
             anchors.fill: parent
             border.left: 5; border.top: 10
             border.right: 5; border.bottom: 5
             width: parent.width
             Image
             {
                 x:0
                 y:0
                 width: parent.height
                 height: width;
                 source:currentSongDisplay.coverURL == "" ? "resources/no_cover.png" : currentSongDisplay.coverURL;
                 id: currentSongCover
                 opacity: 0.2
             }
             Rectangle
             {
                 z:1
                 anchors.right: parent.right
                 anchors.left: currentSongCover.right
                 height: parent.height
                 width: parent.width-currentSongCover.width
                 anchors.top:  parent.top
                 anchors.bottom:  parent.bottom
                 color: "transparent"
                 //opacity:0.7

                 MarqueeText
                 {
                    x: 10 *  root.globalScaleFactor
                    y: 14 *  root.globalScaleFactor
                    text: currentSongDisplay.songName
                    height: 42 *  root.globalScaleFactor;
                    fontSize: 29 *  root.globalScaleFactor
                    color: "#d4d4d4"
                    width: parent.width - 20 * root.globalScaleFactor
                    id: songNameLabel
                    clip: true
                 }

                 Text
                 {
                     y: songNameLabel.height + (18 *   root.globalScaleFactor);
                     x:10 *  root.globalScaleFactor
                     height:35 *  root.globalScaleFactor
                     font.pixelSize: 20 *  root.globalScaleFactor
                     color: "#838383"
                     text: currentSongDisplay.artistName
                     id: artistNameLabel

                 }

                 Text
                 {
                     x: 10 *  root.globalScaleFactor
                     y: songNameLabel.height + artistNameLabel.height + (8 *  root.globalScaleFactor);
                     text: currentSongDisplay.albumName
                     font.pixelSize: 20 *  root.globalScaleFactor
                     color: "#838383"

                 }
            }
         }


        }
        MusicProgress
        {
            y: currentSongDisplay.height-1;
            id: progress
        }

        Rectangle
        {
            anchors.top: progress.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right:  parent.right
            color:"transparent"
            Dialer
            {
                anchors.centerIn:  parent;
                width:root.height/2
                height:width;
            }
        }
    }
}
