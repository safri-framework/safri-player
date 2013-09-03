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

    Item {
        anchors.fill: parent;
        focus: true
        Keys.onVolumeUpPressed:  {volumeChanged(10);console.log("TEST")}
    }


    Canvas
    {
     id: canvas
     objectName: "volumeIndicator"
     property string imagefile:"resources/2-scale-volume.png"
     property int volume
     property double scale: scaleFactor

     antialiasing: true
     Component.onCompleted:loadImage(canvas.imagefile);
     width: parent.height + (60* scaleFactor)
     height: width + 15*scaleFactor
     y: -45 * scaleFactor;
     x: -30 * scaleFactor;
     onPaint: clipIndicator();
     onVolumeChanged: {canvas.requestPaint(); console.log(volume)}

     function clipIndicator()
     {
            var ctx = canvas.getContext("2d");
            ctx.reset()
            ctx.save()

            ctx.clearRect(0, 0, canvas.width, canvas.height);
            ctx.lineWidth = 10
            ctx.beginPath()
            ctx.moveTo(canvas.width/2, canvas.width/2 + 15*scaleFactor)
            ctx.arc(canvas.width/2, canvas.width/2 + 15*scaleFactor, (canvas.width / 2) - 10*scaleFactor , 2.3,  + 2.3 + (4.9 / 100 ) * canvas.volume, false)
            ctx.closePath();
            ctx.clip()
            ctx.drawImage(canvas.imagefile, 0, 0, canvas.width, canvas.width);
            console.log("paint")
            ctx.restore()
     }
    }

    Image{
        source:"resources/6-highlight-fixed.png"
        anchors.centerIn: parent
        width: parent.width-60*scaleFactor
        height:parent.height-60* scaleFactor
        smooth: true
        Image {
        id: dialer
        anchors.verticalCenter: parent.verticalAlignment
        width: parent.width;
        height: parent.width
        source: "resources/5-outer-knob-rotatingII.png"
        opacity:0.8
        smooth:true
        }
    }

    Image
    {

        width: parent.width-60
        height:parent.height-60
        anchors.centerIn: parent;
        source:"resources/3-inner-knob-fixed.png"
        z:-1
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
