// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import "functions.js" as MyJs



Rectangle {
    id: mainframe;
    width: 800;
    height: 480;

        Rectangle
        {
            id: content
            width: parent.width
            height: parent.height-59-footer.height
            x:0
            y:59
            color:"#1b2436"


            MusicSelection
            {
                id: selection
            }

        }
        Rectangle
        {
            BorderImage
            {
                id: headerBoarder
                source: "images/header2.png"
                width: mainframe.width; height: 88
                border.left: 0; border.top: 0
                border.right: 206; border.bottom: 40
                Rectangle
                {

                    id: headerContent
                    width:  594
                    height: 58
                    color: "transparent"


                    Player{}
                }
            }

        } // header


    Rectangle
    {
        id: footer
        height: 58
        width: mainframe.width
        color:"blue"
        anchors.bottom: mainframe.bottom
        gradient:
        Gradient
        {

            GradientStop { position: 0;   color:MyJs.myRGBA(37,46,75,79) }
            GradientStop { position: 1;  color: "#1b2338" }
        }


    }


    }



