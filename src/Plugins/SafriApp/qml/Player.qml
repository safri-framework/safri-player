import QtQuick 2.0

Rectangle {
    property double scaleFactor:1
    onHeightChanged: scaleFactor = height / 97
    color:"black"
    BorderImage
    {
        height:parent.height
        source: "resources/player_border.png"
        horizontalTileMode: BorderImage.Repeat
        verticalTileMode: BorderImage.Stretch
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right:playerImage.left
        border.left: 0
        border.right: 0
        border.bottom: 0
        border.top: 0
    }

    Image {
        id: playerImage
        source: "resources/player_backgroundIII.png"
        anchors.centerIn: parent

        height: parent.height
        width : 433 * scaleFactor
        onScaleChanged: {console.log(width); console.log(height)}
        /*
        MouseArea
        {
            x:68
            y:14
            width:85
            height:70
            onClicked: {console.log("CLICK")}
            id: previous;
        }
        */

        PlayerButton
        {
            x:68 * scaleFactor
            y:14 * scaleFactor
            width:85 * scaleFactor
            height:70 * scaleFactor
            toggle:false
            objectName: "prevButton"
            icon1: "resources/ico_prev.png"

        }
        PlayerButton
        {
            id: playPause
            x:174 * scaleFactor
            y:7 * scaleFactor
            width:85 * scaleFactor
            height:85 * scaleFactor
            toggle:true
            objectName: "playStop";
            icon1: "resources/ico_play.png"
            icon2: "resources/ico_pause.png"

        }
        PlayerButton
        {
            id: next
            x:279 * scaleFactor
            y:14 * scaleFactor
            width:85 * scaleFactor
            height:70 * scaleFactor
            objectName: "nextButton"
            icon1: "resources/ico_next.png"
            toggle:false
        }
    }

    BorderImage
    {
        height:parent.height
        anchors.top: parent.top
        anchors.left: playerImage.right
        anchors.right:parent.right
        source: "resources/player_border.png"
        horizontalTileMode: BorderImage.Repeat
        verticalTileMode: BorderImage.Stretch
        border.left: 0
        border.right: 0
        border.bottom: 0
        border.top: 0
    }
}
