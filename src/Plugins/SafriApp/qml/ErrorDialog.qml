
import QtQuick 2.1
import QtQuick.Controls.Styles 1.0
import QtQuick.Controls 1.0

Rectangle
{

    property var errorMsg;
    MouseArea{anchors.fill: parent}
    width: parent.width * 2/3
    height: contentLayout.height + 20 * root.globalScaleFactor
    //anchors.centerIn: parent
    anchors.horizontalCenter: parent.horizontalCenter
    y: -height


    id: errorDialog

    border.width: 1
    border.color: "black"
    radius: 10 * root.globalScaleFactor
    color:"#1B1B1B"

    opacity: y / (dialogController.height/3)
    property bool connected: false;

    Rectangle
    {
        color:"transparent"
        width: errorDialog.width - 20 * root.globalScaleFactor
        height: errorDialog.height - 20 * root.globalScaleFactor
        x: 10 * root.globalScaleFactor
        y: 10 * root.globalScaleFactor
        id:errorDialogContent

        Column
        {
            spacing: 20 * root.globalScaleFactor
            id:contentLayout
        Row
        {
            spacing: 20 * root.globalScaleFactor

                Image
                {
                    width: 60*root.globalScaleFactor
                    height:width;
                    source:"resources/Error.svg"
                    id: warningIcon
                    opacity:  0.7
                }

            Column
            {
                spacing: 10 * root.globalScaleFactor
                Label
                {
                    width: (errorDialogContent.width-parent.spacing) * 4 / 5;
                    id: headLine
                    objectName: "hostTextField"
                    font.pixelSize: 20 * root.globalScaleFactor;
                    text: "Fehler"
                    color:"white"
                }

                Label
                {
                    z:2000;
                    wrapMode: Text.WordWrap
                    opacity:1
                    width: parent.width
                    id: errorMsgLabel
                    objectName: "hostTextField"
                    font.pixelSize: 16 * root.globalScaleFactor;
                    clip:true
                    color:"white"
                    text: errorMsg
                }
            }
        }


            PlayerButton
            {
                objectName: "errorDialog"
                signal connectTo(var ip, var port)
                height: textFieldHeight
                width: height
                iconScale: 0.5
                smooth:true
                opacity: 0.7
                icon1: "resources/check-inv.png"
                toggle: false
                onButtonClicked: { dialogController.hideError()}
                x: parent.width - width - (10 * root.globalScaleFactor)
            }

        }
    }
}
