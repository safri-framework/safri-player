import QtQuick 2.0
import QtQml.Models 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0



Rectangle {
    id: root
    color: "#272727"
    width: 480
    height: 800
    property bool printDestruction: true
    property double globalScaleFactor: (height / 800) < 0.5 ? 0.5 : height/800
    onHeightChanged:{ globalScaleFactor = (height / 800) < 0.5 ? 0.5 : height/800; console.log("SCALE: "+ globalScaleFactor)}

    MenuBar
    {
        Menu {
            title: "Settings"

            MenuItem {
                objectName: "menuItemDisconnect"
                signal disconnect()
                text: "Safri local"
                shortcut: "Ctrl+L"
                onTriggered: disconnect()
            }


            MenuItem {
                text: "Safri remote"
                shortcut: "Ctrl+R"
                onTriggered:  settingsPage.setVisible = !settingsPage.setVisible
            }
        }
    }



    ObjectModel {
        id: itemModel

        View1{id: view1; }
        View2{}
        View3{}

    }

    Settings
    {
        visible: false
        z:100
        id: settingsPage
    }


    ListView {
        id: view
        anchors { fill: parent; bottomMargin: 120*root.globalScaleFactor}
        model: itemModel
        currentIndex: 1;
        preferredHighlightBegin: 0; preferredHighlightEnd: 0
        highlightRangeMode: ListView.StrictlyEnforceRange
        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem; flickDeceleration: 4000 * root.globalScaleFactor
        cacheBuffer: 200
    }

    Rectangle {
        id: pageIndicator
        width: root.width;
        height: 16 * root.globalScaleFactor
        anchors { top: view.bottom }
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#3c3c3c" }

               GradientStop { position: 1.0; color: "#242424" }
           }

        Row {
            anchors.centerIn: parent
            spacing: root.width / 6

            Repeater {
                model: itemModel.count

                Rectangle {
                    width: 6 * root.globalScaleFactor; height: 6 * root.globalScaleFactor
                    radius: 4 * root.globalScaleFactor
                    opacity: view.currentIndex == index ? 0.8 : 1
                    color: view.currentIndex == index ? "white" : "black"

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
