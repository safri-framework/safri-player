import QtQuick 2.0

import "RotaryDialer.js" as Dialer

Rectangle {


    signal volumeChanged(variant volume)
    property double scaleFactor:height/420
    id: dialerView
    objectName: "dialerView";
    width: parent.width-20*root.globalScaleFactor
    height: width
    anchors.centerIn: parent
    color: "transparent"
    onHeightChanged: {scaleFactor = height / 420;Dialer.initialize(); }
    /*Rectangle
    {
      anchors.fill: parent
      color:"white"
      opacity: 0.5
    }*/

    Image{
        source:"resources/6-highlight-fixed.png"
        anchors.centerIn: parent
        width: parent.width
        height:parent.height
        Image {
        id: dialer
        anchors.verticalCenter: parent.verticalAlignment
        width: parent.width;
        height: parent.width
        source: "resources/5-outer-knob-rotatingII.png"
        opacity:0.6
        }
    }

    Image
    {
        y:2
        source:"resources/3-inner-knob-fixed.png"
        anchors.fill:parent
    }
    // the dialer stop layer



    MouseArea {
	anchors.fill: parent
	onPositionChanged: Dialer.dialerMoved(mouse)
    onReleased: Dialer.dialerReleased(mouse)
	onPressed: Dialer.dialerPressed(mouse)
    }

    Component.onCompleted: Dialer.initialize()
}
