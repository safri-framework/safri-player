// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import "functions.js" as MyJs



Rectangle {
    id: mainframe;
    width: 1280;
    height: 720;
    signal play(variant mIndex)


    Rectangle
    {
        color:"#1b2436"
        id: content
        width: parent.width
        height: parent.height-MyJs.scale(59);
        x:0
        y:MyJs.scale(59)+6

        Loader
        {
            anchors.fill: parent
            property string loaderSource
            id: loader
            opacity: 0
            source: loaderSource

            Behavior on opacity {
                        NumberAnimation{
                            duration: 500
                            easing.type: Easing.OutExpo
                        }

            }
        }
        Connections
        {
            target: loader.item
            onPlayModelIndex: mainframe.play(mIndex)
        }


        Home
        {
            id:homeScreen
        }


    }



            BorderImage
            {
                id: headerBoarder
                source: "images/header2_big.png"
                width: mainframe.width+2; height: MyJs.scale(88);
                border.left: 0; border.top: 0
                border.right: 332; border.bottom: 45

                Rectangle
                {
                    x:parent.width-MyJs.scale(200);
                    y:0
                    z:MyJs.scale(2)
                    width:MyJs.scale(200)
                    height:MyJs.scale(80)
                    color:"transparent"
                    id:clock
                    Timer {
                        interval: 500; running: true; repeat: true
                        onTriggered: timeLabel.text = Qt.formatDateTime(new Date(), "hh:mm")
                    }
                    Text {
                        color: "white"
                        font.family: "Advent"
                        font.pixelSize: 78
                        anchors.centerIn: parent
                        id:timeLabel
                    }
                }

                Rectangle
                {

                    id: headerContent
                    width:  parent.width-MyJs.scale(206)
                    height: MyJs.scale(58)
                    color: "transparent"




                       PlayerButton
                       {
                           x:parent.width-MyJs.scale(60)
                           y:MyJs.scale(4)
                           width:MyJs.scale(50)
                           height:MyJs.scale(50)
                           id: homeButton
                           toggle: false
                           icon1: "images/home-inv.png"
                           onButtonClicked:
                           {
                               console.log("Home")
                               //loader.loaderSource = "Home.qml"
                               loader.opacity = 0
                               homeScreen.opacity = 1
                               //selection.opacity = 0
                               homeButton.enabled = false

                           }

                    }


                    Player
                    {
                        onShowPlaylist:
                        {
                            loader.loaderSource = "MusicSelection.qml"
                            homeScreen.opacity =  0
                            loader.opacity = 1
                            homeButton.enabled = true
                        }


                    }

                }
            }




}



