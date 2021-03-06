import QtQuick 2.2
import QtQuick 2.2

Rectangle{
    property Rectangle currentTapAndHold
    property var nextModelIndex
    property int rowHeight:  root.globalScaleFactor < 0.7 ? parent.height / 5 : parent.height / 7
    property int fontSize: rowHeight / 4;
    property string currentItemText
    property string currentItemImage
    property bool moving
    signal playModelIndexView(variant mIndex)
    signal enqueueModelIndexView(variant mIndex)

    ListModel
    {
        id: listModel
        onRowsInserted:  {currentItemText = listModel.get(listModel.count-1).text}
        onRowsRemoved:
        {
            if(listModel.count == 0)
                currentItemText = "";
            else
                currentItemText = listModel.get(listModel.count-1).text;console.log("test");
        }
    }

    function prevIndex()
    {
        if(listModel.count > 0)
        {
            nextModelIndex = listView.model.parentModelIndex();
            listModel.remove(listModel.count-1)
        }
    }

    function reset()
    {
        listModel.clear();
    }

    id: treeView


    onCurrentItemTextChanged: console.log(currentItemText)
    onNextModelIndexChanged:
    {
        listView.model.rootIndex  = nextModelIndex
    }

    width:parent.width
    height:parent.height

    VisualDataModel {
        onModelUpdated: listView.contentY = 0;
        id: musicQMLModel
        model:musicModel

        delegate:
        Component
        {
            Rectangle
            {
                gradient:
                    Gradient {
                    GradientStop { position: 0.0; color: "#191919" }
                        GradientStop { position: 1.0; color: "black" }
                       }
                height: rowHeight
                id: delegateRect
                width:parent.width

                function calcTextWidth(ownX)
                {
                    if(tapAndHoldPanel.visible)
                    {
                        return tapAndHoldPanel.x - 20 * root.globalScaleFactor - ownX
                    }
                    else
                    {
                        if(!arrow.visible)
                        {
                            return parent.width - ownX - 20 * root.globalScaleFactor
                        }
                        else
                        {
                            return parent.width - ownX - 30 * root.globalScaleFactor - arrow.width
                        }
                    }
                }

                Text
                {
                    text: display
                    color: "#D4D4D4"
                    font.pixelSize: fontSize
                    x:cover.width + 20*root.globalScaleFactor + cover.x
                    width: parent.calcTextWidth(x)
                    anchors.verticalCenter: parent.verticalCenter
                    clip:true
                    id: delegateText
                }


                Rectangle{
                    color: "#424242"
                    height: 1
                    width: parent.width-2
                    x:1
                    y:1
                }

                Image
                {
                    id:arrow
                    source:"resources/Pfeil-Rechts.svg"
                    width: rowHeight/4
                    height: rowHeight * 2/3
                    x: delegateRect.width - width - 10* root.globalScaleFactor
                    anchors.verticalCenter: parent.verticalCenter
                    opacity: 0.2
                    visible: !tapAndHoldPanel.visible && !(type == "SongType")
                }

                MouseArea
                {
                    Timer
                    {
                            id: timer
                            interval: 500; running: false; repeat: false;
                            onTriggered: { parent.dontClick = true}
                    }
                    acceptedButtons: Qt.AllButtons
                    property bool dontClick

                    onReleased: {console.log("release -> timerStop");timer.stop();}
                    anchors.fill: parent
                    onPressAndHold:
                    {
                        tapAndHoldPanel.visible = true; currentTapAndHold = tapAndHoldPanel
                        console.log("pressAndHold")
                    }
                    onClicked:
                    {

                        console.log("clicked " + mouse.button)
                        if(mouse.button == Qt.LeftButton)
                        {
                            if (dontClick)
                            {
                                dontClick = false;
                            }
                            else
                            {
                                if (model.hasModelChildren)
                                {
                                    nextModelIndex = listView.model.modelIndex(index);
                                    listModel.append({"text": delegateText.text, "image": cover.source, "index":nextModelIndex} )                                                                        
                                }
                            }
                        }
                    }
                    onPressed:
                    {
                        if(mouse.button == Qt.LeftButton)
                        {

                            timer.start()
                            if(currentTapAndHold && currentTapAndHold.visible == true)
                            {
                                currentTapAndHold.visible = false;
                                dontClick = true;
                            }
                        }
                        else
                        {
                            tapAndHoldPanel.visible = true; currentTapAndHold = tapAndHoldPanel
                            console.log("pressAndHold")
                        }
                    }
                }
                Rectangle
                {
                    function getImage(type, path)
                    {
                        var returnPath;
                        switch(type)
                        {
                        case  "ArtistType":
                              returnPath = "resources/artist.png";
                              break;
                        case "GenreType":
                             returnPath ="resources/genre.png"
                             break;
                        case "AlbumType":
                            if(path !=="")
                            {
                                returnPath = path;
                            }
                            else
                            {
                                decorationImage.visible = false;
                                noCover.visible = true
                                return "";
                            }
                            break;

                        case "SongType":
                             returnPath = "resources/song.png"
                             break;
                        }
                        noCover.visible = false;
                        decorationImage.visible = true;
                        return returnPath
                    }

                    id: cover
                    color:"transparent"
                    clip:true
                    Component.onCompleted:
                    {
                        if(type == "AlbumType")
                        {
                            width  = delegateRect.height-2;
                            height = delegateRect.height-2;
                            x = 1
                            y = 2
                        }
                        else
                        {
                            width = 30 * root.globalScaleFactor
                            height = width;
                            x = 20 * root.globalScaleFactor
                            anchors.verticalCenter = parent.verticalCenter
                        }
                    }
                    Image
                    {
                        opacity: 0.8
                        source: parent.getImage(type, albumCover)
                        width: parent.width
                        height: parent.height
                        id:decorationImage
                    }
                    Image
                    {
                        opacity: 0.8
                        source: "resources/no_cover2.svg";
                        width: parent.width
                        height: parent.height
                        id:noCover
                        sourceSize.width: 73
                        sourceSize.height: 73
                        antialiasing: false
                        smooth: true
                    }
                }

                Rectangle
                {
                    x: parent.width - tapnHoldImage.width - 10;
                    id:tapAndHoldPanel
                    visible:false

                    Image {
                        id: tapnHoldImage
                        source: "resources/tapnholdpanel2.png"
                        width: 130 * (height/60); height: rowHeight * (2/3)
                        //border.left: 5; border.top: 5
                        y: delegateRect.height/2-tapnHoldImage.height/2


                        PlayerButton
                        {
                            width: tapnHoldImage.width / 2;
                            anchors.verticalCenter: parent.verticalCenter;
                            anchors.left: tapnHoldImage.horizontalCenter;
                            onButtonClicked:
                            {
                                playModelIndexView(listView.model.modelIndex(index));

                                tapAndHoldPanel.visible = false
                            }
                            toggle:false;
                            icon1: "resources/play_icon_black.png";
                        }
                        PlayerButton
                        {
                            width: tapnHoldImage.width / 2;
                            anchors.verticalCenter: parent.verticalCenter;
                            anchors.right: tapnHoldImage.horizontalCenter;
                            onButtonClicked:
                            {
                                enqueueModelIndexView(listView.model.modelIndex(index))
                                console.log("ENQUEUE  CLICK")
                                tapAndHoldPanel.visible = false
                            }
                            toggle:false;
                            icon1: "resources/add.png" ;
                            opacity: 0.7
                            iconScale: 0.7

                        }
                    }
                }
            }
    }
}



ListView {

anchors.fill: parent
model:musicQMLModel
id: listView

onMovementStarted: {treeView.moving = true; timer.stop();}
onMovementEnded:   treeView.moving = false;

section.property: musicQMLModel.count > 100 ? "display":"" ;
section.criteria: ViewSection.FirstCharacter
section.delegate: musicQMLModel > 100 ? sectionHeading : dummy
section.labelPositioning: section.labelPositioning |= ViewSection.CurrentLabelAtStart


}

Component
{
  id:dummy
  Rectangle
  {

  }
}

Component {
    id: sectionHeading

    Rectangle {
        visible:false;
        width: parent.width
        height:20
        gradient:
            Gradient {
                GradientStop { position: 0.0; color: "#424242" }
                GradientStop { position: 1.0; color: "#2b2b2b" }
               }

        Text {
            x:5
            text: section
            font.bold: true
            font.pixelSize: 20
            color: "#AFAFAF"
            anchors.verticalCenter: parent.verticalCenter

        }



        Rectangle
        {
            color:"#161616"
            height:parent.height
            width:1
            x:parent.width-1
            y:0
        }

        Rectangle
        {
            color:"#161616"
            height:parent.height
            width:1
            x:0
            y:0
        }
    }
}


}
