// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import "functions.js" as MyJs

Item{
    id:player
    signal showPlaylist
    Rectangle
    {
        x:MyJs.scale(10)
        y:MyJs.scale(6)
        color: "transparent"
        id: playerContent

        //parent: footer
        width:MyJs.scale(315)
        height:MyJs.scale(45)
        BorderImage
        {
           // anchors.top: parent.top
            x:-6
            y:-6
            id: playerBorderImage
            source: "images/player_big.png"
            width:parent.width+MyJs.scale(10); height:MyJs.scale(53)
            border.left: 32; border.top: 26
            border.right: 26; border.bottom: 32
                opacity:0.5
        }

     PlayerButton
     {
         id:silentButton
         objectName: "silentButton"
          toggle: false;
          icon1: "images/media-volume-0-inv.png"
     }
     PlayerButton
     {
         id:prevButton
         objectName: "prevButton"
         x:  silentButton.width;
          toggle: false;
          icon1:"images/media-previous-inv.png"
     }
     PlayerButton
     {
         id:playStop
         objectName: "playStop"
         x:  2* silentButton.width;
          toggle: true;
     }
     PlayerButton
     {
         id:nextButton
         objectName: "nextButton"
         x:  3* silentButton.width;
          toggle: false;
          icon1:"images/media-next-inv.png"
     }
     PlayerButton
     {
         id:test4
         x:  4* silentButton.width;
          toggle: false;
          onButtonClicked: player.showPlaylist()
          icon1:"images/open-in-new-window-inv.png"
     }

    }
}
