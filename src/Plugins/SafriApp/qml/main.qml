import QtQuick 2.0
import QtQml.Models 2.1

Rectangle {
    id: root
    color: "lightgray"
    width: 480
    height: 800
    property bool printDestruction: true
    property double globalScaleFactor: height/800
    onHeightChanged: globalScaleFactor = height / 800


//! [0]
    ObjectModel {
        id: itemModel

        View1{id: view1; }
        View2{}

        View1{}
        Rectangle {
            width: view.width; height: view.height
            color: "#F0FFF7"
            Text { text: "Page 2"; font.bold: true; anchors.centerIn: parent }

            Component.onDestruction: if (printDestruction) print("destroyed 2")
        }
        Rectangle {
            width: view.width; height: view.height
            color: "#F4F0FF"
            Text { text: "Page 3"; font.bold: true; anchors.centerIn: parent }

            Component.onDestruction: if (printDestruction) print("destroyed 3")
        }
    }

    ListView {
        id: view
        anchors { fill: parent; bottomMargin: root.height / 6}
        model: itemModel
        preferredHighlightBegin: 0; preferredHighlightEnd: 0
        highlightRangeMode: ListView.StrictlyEnforceRange
        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem; flickDeceleration: 2000
        cacheBuffer: 200
    }
//! [0]
    Rectangle {
        id: pageIndicator
        width: root.width;
        height: 14 * root.globalScaleFactor
        anchors { top: view.bottom }
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#5A5A5A" }

               GradientStop { position: 1.0; color: "#252525" }
           }

        Row {
            anchors.centerIn: parent
            spacing: 20

            Repeater {
                model: itemModel.count

                Rectangle {
                    width: 5 * root.globalScaleFactor; height: 5 * root.globalScaleFactor
                    radius: 3 * root.globalScaleFactor
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

    Player
    {
        anchors{top: pageIndicator.bottom; bottom: root.bottom; right: root.right; left: root.left}

    }
}

