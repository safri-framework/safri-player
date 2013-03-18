// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1


Item{


    Rectangle
    {
        x:10
        y:6
        color: "transparent"
        id: player

        //parent: footer
        width:315
        height:45
        BorderImage
        {
           // anchors.top: parent.top
            x:-6
            y:-3
            id: playerBorderImage
            source: "images/player.png"
            width:parent.width+10; height:53
            border.left: 20; border.top: 20
            border.right: 20; border.bottom: 20
                opacity:0.5
        }

     PlayerButton
     {
         id:test
          toggle: false;
     }
     PlayerButton
     {
         id:test1
         x:  test.width;
          toggle: false;
     }
     PlayerButton
     {
         id:test2
         x:  2* test.width;
          toggle: false;
     }
     PlayerButton
     {
         id:test3
         x:  3* test.width;
          toggle: false;
     }
     PlayerButton
     {
         id:test4
         x:  4* test.width;
          toggle: false;
     }

    }
}
