import QtQuick 2.0
import QtQml.Models 2.1

Rectangle {
    id: root
    color: "lightgray"
    width: 480
    height: 800
    property bool printDestruction: true
    property double globalScaleFactor: (height / 800) < 0.5 ? 0.5 : height/800
    onHeightChanged:{ globalScaleFactor = (height / 800) < 0.5 ? 0.5 : height/800; console.log("SCALE: "+ globalScaleFactor)}

    ObjectModel {
        id: itemModel

        View1{id: view1; }
        View2{}
        View3{}
    }

    ListView {
        id: view
        anchors { fill: parent; bottomMargin: 120*root.globalScaleFactor}
        model: itemModel
        currentIndex: 1;
        preferredHighlightBegin: 0; preferredHighlightEnd: 0
        highlightRangeMode: ListView.StrictlyEnforceRange
        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem; flickDeceleration: 2000
        cacheBuffer: 200
    }

    Rectangle {
        id: pageIndicator
        width: root.width;
        height: 16 * root.globalScaleFactor
        anchors { top: view.bottom }
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#5A5A5A" }

               GradientStop { position: 1.0; color: "#252525" }
           }

        Row {
            anchors.centerIn: parent
            spacing: root.width / 6

            Repeater {
                model: itemModel.count

                Rectangle {
                    width: 6 * root.globalScaleFactor; height: 6 * root.globalScaleFactor
                    radius: 4 * root.globalScaleFactor
                    color: view.currentIndex == index ? "#868786" : "#131313"

                    MouseArea {
                        width: 20; height: 20
                        anchors.centerIn: parent
                        onClicked: view.currentIndex = index
                    }
                }
            }
        }
    }
    Rectangle
    {
        anchors{top: pageIndicator.bottom; bottom: root.bottom; right: root.right; left: root.left}
        color:"green"
        Player
        {
            anchors.fill: parent
        }
    }
}
