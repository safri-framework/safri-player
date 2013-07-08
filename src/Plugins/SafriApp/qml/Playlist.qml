import QtQuick 2.0

Rectangle{
    property Rectangle currentTapAndHold
    property int rowHeight: root.globalScaleFactor < 0.7 ? parent.height / 5 : parent.height / 7
    property int fontSize:  rowHeight / 3
    property bool moving
    signal movePos(variant from, variant to)
    property int newDragPosition:0
    property int draggedIndex;
    property bool reset: false;
    property bool animated: true;
    id: playList
    objectName: "playList"
    width:parent.width
    height:parent.height
    color:"transparent"
    clip:true
    signal itemHasMoved
    signal released
    onNewDragPositionChanged:    
    {
        if(animated && newDragPosition % 2 == 0)
            itemHasMoved();
    }

    function release()
    {
        released()
    }

    VisualDataModel {
        id: playlistQMLModel
        model:playlistModel
        delegate:
        Component
        {

            Rectangle
            {
                gradient:

                    Gradient
                    {
                GradientStop { position: 0.0; color: !isPlaying? "#191919" : "#262626"}
                        GradientStop { position: 1.0; color: !isPlaying?"black": "#303030"}
                    }


                Component.onCompleted:
                {
                    playList.itemHasMoved.connect(itemMoved)
                    playList.released.connect(delReleased)
                }

                signal itemMoved();
                signal delReleased();
                property int globalItemIndex: index;
                height: rowHeight
                id: plDelegateRect
                width:parent.width
                objectName: "plDelegate"
                anchors.topMargin: 50
                property int offset;
                property int oldy: y;
                property bool movedUp: false;
                property bool movedDown: false;
                property bool firstMove: true;
                property bool reset;
                onDelReleased:
                {
                    reset = true;
                    movedUp = false;
                    movedDown = false;
                    reset = false;
                    firstMove = true;
                }

                onItemMoved:
                {
                    if( index > draggedIndex)
                    {
                        if(playList.newDragPosition + rowHeight/2 > oldy  )
                        {
                            movedUp =  true;
                            return;
                        }
                        else
                        {
                            movedUp = false;
                            return;
                        }
                    }
                    if( index < draggedIndex)
                    {
                        if(playList.newDragPosition - rowHeight/2 < oldy  )
                        {
                            movedDown =  true;
                            return;
                        }
                        else
                        {
                            movedDown = false;
                            return;
                        }
                    }
                }


                PropertyAnimation
                {
                    id: moveAnimation
                    target: plDelegateRect
                    property:"y"
                    to: y-rowHeight
                    duration: 200
                }

                onMovedUpChanged:
                {
                    if(plDelegateRect.movedUp)
                    {
                        if(firstMove)
                        {
                            oldy = y;
                            firstMove = false;
                        }
                        moveAnimation.complete()
                        moveAnimation.to =  y - rowHeight
                        moveAnimation.start()
                    }
                    else
                    {
                        if(!reset)
                        {
                            moveAnimation.complete()
                            moveAnimation.to  = oldy;
                            moveAnimation.start()
                        }
                        else
                        {
                            moveAnimation.complete()
                            y = oldy;
                        }
                    }
                }

                onMovedDownChanged:
                {
                    if(plDelegateRect.movedDown)
                    {
                        if(firstMove)
                        {
                            oldy = y;
                            firstMove = false;
                        }
                        moveAnimation.complete()
                        moveAnimation.to  = y + rowHeight
                        moveAnimation.start()
                    }
                    else
                    {
                        if(!reset)
                        {
                            moveAnimation.complete()
                            moveAnimation.to  = oldy;
                            moveAnimation.start()
                        }
                        else
                        {
                            moveAnimation.complete()
                            y = oldy;
                        }
                    }
                }

                Text
                {
                    text: song
                    color: "#D4D4D4"
                    font.pixelSize: fontSize
                    x: 20 * root.globalScaleFactor
                    y: rowHeight / 7
                    //anchors.verticalCenter: parent.verticalCenter
                    id: songText
                    width: parent.width - 2*x
                    clip:true
                }

                Text
                {
                    text: album
                    color: "#838383"
                    font.pixelSize: fontSize * 0.6
                    x:20 * root.globalScaleFactor;
                    y: songText.y + songText.height + 5 * root.globalScaleFactor;
                    width: parent.width - 2*x
                    id: artistText
                    clip: true
                }

                Rectangle
                {
                    color: "#424242"
                    height: 1
                    width: parent.width-2
                    x:1
                    y:1
                }

                MouseArea {

                    function startDragAndDrop()
                    {
                        draggedIndex = index;
                        positionStarted = plDelegateRect.y;
                        dragArea.drag.target = plDelegateRect;
                        plDelegateRect.opacity = 0.5;
                        pListView.interactive = false;
                        held = true;
                        drag.maximumY = playlistQMLModel.count * rowHeight;
                        drag.minimumY = 0
                        plDelegateRect.z = 1000
                        console.log("press")
                    }

                    acceptedButtons: Qt.AllButtons
                     id: dragArea
                     anchors.fill: parent
                     property int positionStarted: 0
                     property int positionEnded: 0
                     property int positionsMoved: Math.floor((((positionEnded) - (positionStarted))+rowHeight/2)/rowHeight)
                     property int newPosition: position + positionsMoved
                     property bool held: false
                     property bool moved:false

                    drag.axis: Drag.YAxis
                    onPositionChanged:
                    {
                        if(held)
                        {
                            positionEnded = plDelegateRect.y;
                            newDragPosition = plDelegateRect.y;
                            if(Math.abs(positionStarted-positionEnded) > 30*root.globalScaleFactor)
                                moved = true;
                        }
                    }

                    onPressed: if(view2.editMode) startDragAndDrop()


                     onReleased:
                        {
                            console.log("release")
                            if(animated)
                            {
                                playList.release();
                            }
                            pListView.interactive = true
                            console.log("start: "+position+"  end:"+newPosition)

                            if (Math.abs(positionsMoved) < 1 && held == true)
                            {
                                plDelegateRect.y = positionStarted
                                plDelegateRect.opacity = 1
                                pListView.interactive = true
                                dragArea.drag.target = null
                                held = false
                                plDelegateRect.y = positionStarted;
                                newDragPosition = -1;
                            }
                            else
                            {
                                if (held == true && moved)
                                {
                                    if (newPosition < 1)
                                    {
                                        plDelegateRect.z = 1
                                        movePos(position, 0)
                                        plDelegateRect.opacity = 1

                                        dragArea.drag.target = null
                                        held = false
                                        plDelegateRect.y = positionStarted;
                                        pListView.forceLayout();
                                        // playlistQMLModel.items.move(index,0,1)
                                    }
                                    else if (newPosition > pListView.count - 1)
                                    {
                                        plDelegateRect.z = 1
                                        movePos(position,pListView.count - 1)
                                        plDelegateRect.opacity = 1

                                        dragArea.drag.target = null
                                        // playlistQMLModel.items.move(index,pListView.count - 1,1)
                                        held = false
                                        plDelegateRect.y = positionStarted;
                                        pListView.forceLayout();
                                    }
                                    else
                                    {
                                        plDelegateRect.z = 1
                                        movePos(position,newPosition)
                                        plDelegateRect.opacity = 1

                                        dragArea.drag.target = null
                                        // playlistQMLModel.items.move(index,newPosition,1)
                                        held = false
                                        plDelegateRect.y = positionStarted;
                                        pListView.forceLayout();
                                    }
                                }
                                else
                                {
                                    plDelegateRect.opacity = 1
                                }
                            }
                        }
                 }
            }
    }
}



ListView {

anchors.fill: parent
model:playlistQMLModel
id: pListView

onMovementStarted: playList.moving = true;
onMovementEnded:   playList.moving = false;



}




}
