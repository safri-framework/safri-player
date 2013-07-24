import QtQuick 2.0

Rectangle {

    width: view.width
    height: view.height
    color: "#272727"
    id:view2
    property bool editMode: editModeButton.enabled;

    Rectangle
    {

        width: view.width - 20  * root.globalScaleFactor
        height: view.height - 30 * root.globalScaleFactor - menu.height
        radius: 10 * root.globalScaleFactor
        x:10 * root.globalScaleFactor;
        y:10 * root.globalScaleFactor;
        color:"#1B1B1B"

        Playlist{id: playlist}


    }
    Rectangle
    {
        id:menu
        x:10 * root.globalScaleFactor;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 10 * root.globalScaleFactor;
        height: 45 * root.globalScaleFactor;
        width: parent.width - 20 * root.globalScaleFactor
        radius: 10 * root.globalScaleFactor
        color:"#1B1B1B"

        Rectangle
        {
            color: "transparent"
            width: menu.width / 3
            height: menu.height
            x:0
            y:0
            PlayerButton
            {
                width: parent.width
                height: parent.height
                checkable: true
                iconScale: 0.5
                icon1: "resources/media-repeat-inv.png"
            }
        }
        Rectangle
        {
            width: menu.width / 3
            height: menu.height
            color: "transparent"
            x:(menu.width / 3) * 1
            y:0
            PlayerButton
            {
                width: parent.width
                height: parent.height
                checkable: true
                iconScale: 0.5
                //enabled: true
                icon1: "resources/media-shuffle-inv.png"
                objectName: "shuffleButton";
            }
        }
        Rectangle
        {
            width: menu.width / 3
            height: menu.height
            color: "transparent"
            x:(menu.width / 3) * 2
            y:0
            PlayerButton
            {
                width: parent.width
                height: parent.height
                icon1: "resources/pencil-inv.png"
                iconScale: 0.5
                checkable: true
                onEnabledChanged: view.interactive = !enabled
                id: editModeButton
            }
        }

    }
}
