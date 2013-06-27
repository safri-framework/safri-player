import QtQuick 2.0

Rectangle {


    property string totalTime: ""
    property string currentTime: ""

    function timeToString(val)
    {
        var tmp = val / 1000;
        var min = Math.floor(tmp / 60);

        if (min < 10)
        {
            min = "0"+min;
        }

        var s = Math.round(tmp  % 60);

        if (s < 10)
        {
            s = "0"+s;
        }

        return min.toString() + ":"+s.toString()
    }

    function setProgress(total, curr)
    {
        musicProgress.visible = true;
        totalTime       = timeToString(total);
        currentTime     = timeToString(curr);

        var pWidth = innerProgress.parent.width;
        var width = pWidth * (curr / total);
        innerProgress.width = width;
    }

    objectName: "musicProgress"
    id: musicProgress
    visible:false;
    width: parent.width
    height: 30
    gradient:
        Gradient {
            GradientStop { position: 0.0; color: "#191919" }
            GradientStop { position: 1.0; color: "black" }
           }
    Rectangle{
        color: "#424242"
        height: 1
        width: parent.width-2
        x:1
        y:1
    }


    Rectangle
    {
        id: text1Rec
        anchors.right: outerProgress.left
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

        Text
        {
            id: text1
            anchors.centerIn: parent;
            text: currentTime
            color:"grey"
        }
    }
        Rectangle
        {
            id: outerProgress
            anchors.left: text1.right
            anchors.centerIn: parent
            height: 8
            width: parent.width-100
            gradient:
                Gradient {
                    GradientStop { position: 0.0; color: "#474747" }
                    GradientStop { position: 1.0; color: "#2c2c2c" }
                   }
            radius: 5

            Rectangle
            {
                id:innerProgress
                x: 0
                y: 0
                height: parent.height
                width: 0
                gradient:
                    Gradient {
                        GradientStop { position: 0.0; color: "#AFAFAF" }
                        GradientStop { position: 1.0; color: "#545454" }
                       }
                radius: 5
            }
        }
        Rectangle
        {
            id: text2Rect
            anchors.right: parent.right
            anchors.left: outerProgress.right
            anchors.verticalCenter: parent.verticalCenter


            Text
            {
                anchors.centerIn: parent
                id: text2
                text:totalTime
                color:"grey"
            }
        }

    }

