import QtQuick 2.0

Item {
    id:marqueeText
    height: scrollingText.height
    clip: true
    property int tempX: 0
    property alias text: scrollingText.text
    property alias color: scrollingText.color
    property alias fontSize: scrollingText.font.pixelSize

    onTextChanged:
    {
        if ( scrollingText.width > parent.width)
        {
        tempX = 0;
        timer.running = true;
        }
    }

    Text {
        x: tempX
        id:scrollingText
    }

    MouseArea {
        id:mouseArea
        anchors.fill: parent
        onClicked: {
            tempX = 0;
            timer.running = true;
        }
    }

    Timer {
        id:timer
        interval: 200; running: false; repeat: true
        onTriggered:{
            tempX = tempX + 5
            scrollingText.x = -tempX;

            if( tempX + marqueeText.width > scrollingText.width ) {
                timer.running = false
                pauseTimer.running = true
            }
        }
    }

    Timer {
        id:pauseTimer
        interval: 500; running: false; repeat: false
        onTriggered: {
            scrollingText.x = 0
        }
    }
}
