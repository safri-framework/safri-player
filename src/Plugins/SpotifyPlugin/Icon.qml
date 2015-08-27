import QtQuick 2.0
import "Helpers.js" as Helpers
Rectangle
{
    id:root
    color:"transparent"
    width: 32
    height: 32
    property int iconSize: 16
    property int iconSizeHover: 20

    property alias icon: textLabel.text
    property color iconColor: !mouseArea.containsMouse ? Helpers.transparentColor("ffffff",60) : "white"
  //   Behavior on iconColor {ColorAnimation{duration: 100}}
    property string iconFont: fontLoader.name
    signal clicked()

    MouseArea
    {
        id:mouseArea
        anchors.fill: parent
        hoverEnabled: true
        preventStealing: true
        onClicked:root.clicked()
    }

    FontLoader {id: fontLoader; source: "qrc:/iconfont"}
    Text
    {
        text: "hallo"
        id:textLabel
        font.pixelSize: mouseArea.containsMouse? root.iconSizeHover : root.iconSize
        Behavior on font.pixelSize {NumberAnimation{duration:50}}
        color: root.iconColor
        font.family: root.iconFont
        anchors.centerIn: parent
    }



    property variant icons:
    {
        "addtolist": "",
        "play":"",
        "spotify": "",
        "coverflow":"",
        "covergrid":"",
        "list": "",
        "star":"",
    }
}
