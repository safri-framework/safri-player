import QtQuick 2.0

import "RotaryDialer.js" as Dialer

Rectangle {

    property double scaleFactor :1

    signal volumeChanged(variant volume)
    id: dialerView
    objectName: "dialerView";
    width: 340
    height: 340
    anchors.centerIn: parent
    color: "transparent"
    onHeightChanged: {Dialer.initialize(); scaleFactor = height / 340}

    Image {
	id: dialer
    anchors.centerIn: parent
    width: parent.width;
    height: parent.width
    source: "resources/knob.png"
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
