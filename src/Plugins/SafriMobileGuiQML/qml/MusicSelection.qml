// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import "functions.js" as MyJs
Rectangle
{
    id: innerContent
    width: parent.width-20
    height: parent.height-20;
    anchors.centerIn: parent
    color: Qt.rgba(1,1,1,0.2)
    clip: true

    radius: 10
    Rectangle
    {
        id:menuLeft
        color:"transparent"
        height: parent.height
        width: 120
        BorderImage
        {
            y:-5
            x:-3
            id: name
            source: "images/element_musicSelection_left.png"
            width: parent.width; height: parent.height+10
            border.left: 12; border.top: 12
            border.right: 12; border.bottom: 12
        }

        MouseArea {
                 id: mouseArea
                 anchors.fill: parent
                 onClicked:
                 {
                    if(parent.state !== "moved")
                    {
                        parent.state ="moved"
                    }
                    else
                    {
                        parent.state ="default";
                    }
                 }
             }

             states: State {
                 name: "moved"; when: mouseArea.clicked
                 PropertyChanges { target: menuLeft; width: 50;  }
             }

             transitions: Transition {
                 NumberAnimation { properties: "width"; easing.type: Easing.InOutQuad }
             }
    }

    ListView {
        x: menuLeft.width -10
        y:1
        width: parent.width - menuLeft.width + 10; height: parent.height
        id: listView
        model: dataModel
        delegate:
            Component
            {
               id: delegate
                Rectangle
                {
                    height: 50
                    width: parent.width

                    color:
                        if(index % 2 == 0)
                        {
                            MyJs.myRGBA(255,255,255,10)
                        }
                        else
                        {
                            MyJs.myRGBA(255,255,255,5)
                        }

                    id:delegateRect

                    Text
                    {
                        x:12
                        y:2
                        text: name
                        font.pixelSize: 36
                        color: "black"
                        opacity: 0.3

                    }
                    Text
                    {
                        x:10
                        text: name
                        font.pixelSize: 36
                        color: "white"
                        opacity: 0.8

                    }

                }
            }
        }



    ListModel {
        id: dataModel
         ListElement {
             name: "RedHotChiliPeppers"
             number: "555 3264"
         }
         ListElement {
             name: "BlueBookBand"
             number: "555 8426"
         }
         ListElement {
             name: "Sam Wise"
             number: "555 0473"
         }
         ListElement {
             name: "Sam"
             number: "555 0473"
         }
         ListElement {
             name: "Gentleman"
             number: "555 0473"
         }
         ListElement {
             name: "Akua Naru"
             number: "555 0473"
         }
         ListElement {
             name: "Seeed"
             number: "555 0473"
         }
         ListElement {
             name: "Sam Wise"
             number: "555 0473"
         }
         ListElement {
             name: "Sam Wise"
             number: "555 0473"
         }
         ListElement {
             name: "RedHotChiliPeppers"
             number: "555 3264"
         }
         ListElement {
             name: "BlueBookBand"
             number: "555 8426"
         }
         ListElement {
             name: "Sam Wise"
             number: "555 0473"
         }
         ListElement {
             name: "Sam"
             number: "555 0473"
         }
         ListElement {
             name: "Gentleman"
             number: "555 0473"
         }
         ListElement {
             name: "Akua Naru"
             number: "555 0473"
         }
         ListElement {
             name: "Seeed"
             number: "555 0473"
         }
         ListElement {
             name: "Sam Wise"
             number: "555 0473"
         }
         ListElement {
             name: "Sam Wise"
             number: "555 0473"
         }
     }

}


