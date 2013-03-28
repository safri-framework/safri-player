// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import "functions.js" as MyJs


Rectangle
{
    id: selectionWindow
    signal playModelIndex(variant mIndex)
    width: parent.width
    height: parent.height

    Rectangle{
        width: parent.width
        height: parent.height-footer.height
        color:"#1b2436"
            Rectangle
            {

                id: innerContent
                width: parent.width-MyJs.scale(20)
                height: parent.height-MyJs.scale(20);
                anchors.centerIn: parent
                color: Qt.rgba(1,1,1,0.05)

                clip: true

                radius: MyJs.scale(10)

                Rectangle
                {
                    id:menuLeft
                    color:"transparent"
                    height: parent.height
                    width: MyJs.scale(120)

                    BorderImage
                    {
                        y:-5
                        x:-3
                        z: 2
                        id: name
                        source: "images/element_musicSelection_left_big.png"
                        width: parent.width; height: parent.height+MyJs.scale(10)
                        border.left: 26; border.top: 26
                        border.right: 12; border.bottom: 26
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
                             PropertyChanges { target: menuLeft; width: MyJs.scale(50);  }
                         }

                         transitions: Transition {
                             NumberAnimation { properties: "width"; easing.type: Easing.InOutQuad }
                         }
                }

                Rectangle
                {
                    height:MyJs.scale(20)
                    width: parent.width -12
                    x: 12
                    y: 1
                    opacity: 1
                    z:-1


                    Text
                    {

                    }
                    BorderImage {
                        id: playlistHeader
                        source: "images/playlistHeader_big.png"
                        width: parent.width; height: parent.height
                        border.left: 0; border.top: 0
                        border.right: 0; border.bottom: 0
                    }
                }

                Rectangle
                {

                    z:-2;
                    x: subMenu.width + subMenu.x
                    y:MyJs.scale(21)
                    width: parent.width - 12;
                    height: parent.height-MyJs.scale(21)
                    clip: true
                    color:"transparent"

                    TreeView{
                     id:listView
                     z:-5
                    }
                }

                Rectangle
                {
                    color: "transparent"
                    id: subMenu
                    x:  MyJs.scale(50)-10
                    width: MyJs.scale(70);
                    height: parent.height;
                    BorderImage {
                        id: subMenuBorderImage
                        source: "images/behind_player_menu_background.png"
                        width: parent.width; height: parent.height
                        border.left: 0; border.top: 0
                        border.right: 1; border.bottom: 0
                    }
                    opacity: 0.3
                    z:-5

                }

            VisualDataModel {
                id: musicQMLModel
                delegate:

                    Component
                    {

                        Rectangle
                        {

                            height: MyJs.scale(50)
                            width: parent.width-subMenu.x-subMenu.width+10
                            id: delegateRect
                            z: -4
                            PlayerButton
                            {
                                width: MyJs.scale(20)
                                z:MyJs.scale(1)
                                x: parent.width-MyJs.scale(20)-width
                                toggle: false
                                opacity: 0.4
                                onButtonClicked:
                                {

                                    selectionWindow.playModelIndex(listView.currentView.model.modelIndex(index))
                                }
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    if (model.hasModelChildren)
                                       // listView.model.rootIndex = listView.model.modelIndex(index)
                                        listView.nextIndex(listView.currentView.model.modelIndex(index))
                                }
                            }
                            color:
                                if(index % 2 == 0)
                                {
                                    MyJs.myRGBA(255,255,255,10)
                                }
                                else
                                {
                                    MyJs.myRGBA(255,255,255,5)
                                }




                            Text
                            {

                                x:mainText.x+2
                                y:mainText.y+2
                                text: display
                                font.pixelSize: 42
                                color: "black"
                                opacity: 0.4

                            }
                            Text
                            {
                                anchors.verticalCenter:  parent.verticalCenter
                                id: mainText
                                x: delegateRect.height + 16
                                text: display
                                font.pixelSize: 42
                                color: "white"
                                opacity: 0.8

                            }
                            Image
                            {
                                x:0
                                y:0
                                opacity: 0.8
                                height: delegateRect.height;
                                width: delegateRect.height;
                                z:-2

                                source: albumCover
                            }

                        }
                    }
                model: musicModel
                }



                Behavior on opacity {
                    NumberAnimation{
                        duration: 500
                        easing.type: Easing.OutExpo
                    }
                }

                }
            }
    Footer
    {
        id:footer
        PlayerButton
        {
           x:MyJs.scale(30);
           width: MyJs.scale(20)
           toggle: false
           icon1: "images/arrow-left-inv.png"
           onButtonClicked:
           {
               console.log("TEST")
               listView.prevIndex();
           }
        }
        PlayerButton
        {
           width:MyJs.scale(20);
           x: parent.width-MyJs.scale(30)-width
           toggle: false
           icon1:  "images/arrow-right-inv.png"
        }

    }
}
