import QtQuick 2.0
import "functions.js" as MyJs
// This is available in all editors.


Rectangle
{
    id: footer
    height: MyJs.scale(58)
    width: parent.width
    color:"white"
    anchors.bottom: parent.bottom
    Rectangle{

        height:parent.height
        width: parent.width
        gradient:
        Gradient
        {

            GradientStop { position: 0;   color:MyJs.myRGBA(37,46,75,79) }
            GradientStop { position: 1;  color: "#1b2338" }
        }

        Rectangle
        {
            color:"black"
            height: 1
            anchors.top: parent.top
            width: parent.width
            opacity: 0.3
        }
    }
}
