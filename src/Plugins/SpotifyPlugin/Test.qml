//import QtQuick 2.0
//import QtQuick.Layouts 1.1
//Rectangle
//{
//    width: 100
//    height: 62
//    color: "grey"
//    ExpandableContainer
//    {
//        anchors.fill: parent
//        Expandable
//        {
//            Rectangle{color:"green"; Layout.fillWidth: true;Layout.fillHeight: true}
//            expandedHeight: 200
//            fixHeight: true


//        }

//        Expandable
//        {
//            Rectangle{color:"blue"; Layout.fillWidth: true;Layout.fillHeight: true}
//            expandedHeight:  200
//        }

//        Expandable
//        {
//            Rectangle{color:"red"; Layout.fillWidth: true; Layout.fillHeight: true}
//            expandedHeight: 200
//        }
//    }

//}



import QtQuick.Layouts 1.0
import QtQuick 2.0

Item {
    width: 300; height: 600

    DropArea {
        width: 100; height: 100; anchors.centerIn: parent

        Rectangle {
            anchors.fill: parent
            color: parent.containsDrag ? "red" : "green"
        }

        onEntered: print("entered");
        onExited: print("exited");
        onDropped: print("dropped");
    }

    Rectangle {
        x: 15; y: 15; width: 30; height: 30; color: "blue"

        // I've added this property for simplicity's sake.
        property bool dragActive: dragArea.drag.active

        // This can be used to get event info for drag starts and
        // stops instead of onDragStarted/onDragFinished, since
        // those will neer be called if we don't use Drag.active
        onDragActiveChanged: {
            if (dragActive) {
                print("drag started")
               // Drag.start();
            } else {
                print("drag finished")
               // Drag.drop();
            }
        }

        Drag.active: dragActive
        Drag.dragType: Drag.Automatic
       Drag.mimeData: {"hallo":"welt"}
        // These are now handled above.
        //Drag.onDragStarted: print("drag started");
        //Drag.onDragFinished: print("drag finished");

        MouseArea {
            id: dragArea
            anchors.fill: parent
            drag.target: parent
        }
    }


    Rectangle
    {
       // anchors.fill: parent
        color: "green"
        width: 40
        height: 40
        id: draggable
        Drag.active: mouseArea.drag.active
      //  Drag.hotSpot.x: 0
      //  Drag.hotSpot.y: 0
    //    Drag.onDragStarted:  Drag.mimeData = { "MediaInfoContainer": container }


        Drag.dragType: Drag.Automatic
        MouseArea
        {
//            RowLayout
//            {
//                width: parent.width
//                height: 40

//                spacing: 0
//                Icon{ icon: icons.play;height: parent.height}
//                Icon{ icon: icons.addtolist;height: parent.height}
//                Item{Layout.fillWidth: true}
//                Icon{ icon: icons.star;height: parent.height }
//            }

          //  drag.onActiveChanged: print(drag.active+" ACTIVE?")
          //  preventStealing: true
          //  hoverEnabled: true
            anchors.fill: parent
            id: mouseArea
            drag.target: draggable
           // onClicked: root.clicked()
            //propagateComposedEvents: true
        }



    }
}
