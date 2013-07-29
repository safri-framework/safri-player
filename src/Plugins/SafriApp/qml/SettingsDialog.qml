
import QtQuick 2.1
import QtQuick.Controls.Styles 1.0
import QtQuick.Controls 1.0

Rectangle
{

    MouseArea{anchors.fill: parent}
    width: parent.width * 2/3
    height: 3*textFieldHeight + 60 * root.globalScaleFactor//*root.globalScaleFactor
    //anchors.centerIn: parent
    anchors.horizontalCenter: parent.horizontalCenter
    y: -height


    id: settings

    border.width: 1
    border.color: "black"
    radius: 10 * root.globalScaleFactor
    color:"#1B1B1B"

    opacity: y / (dialogController.height/3)
    property bool connected: false;

    Rectangle
    {
        color:"transparent"
        width: settings.width - 20 * root.globalScaleFactor
        height: settings.height - 20 * root.globalScaleFactor
        x: 10 * root.globalScaleFactor
        y: 10 * root.globalScaleFactor
        id:settingsContent

        Column
        {
            spacing: 20 * root.globalScaleFactor

            Row
            {
                spacing: 20 * root.globalScaleFactor
                Label
                {
                    width: (settingsContent.width-parent.spacing) / 5;
                    text: "IP"
                    color: "white"
                    horizontalAlignment: Text.AlignRight
                    id: ipLabel
                    height: 30 * root.globalScaleFactor
                    verticalAlignment: Text.AlignVCenter
                }

                TextField
                {
                    width: (settingsContent.width-parent.spacing) * 4 / 5;
                    horizontalAlignment: Text.AlignRight
                    id: hostTextField
                    objectName: "hostTextField"
                    style: textfieldStyle
                    height: textFieldHeight
                }
            }



            Row{
                spacing: 20 * root.globalScaleFactor

                Label
                {
                width: (settingsContent.width-parent.spacing) / 5;
                text: "Port"
                color: "white"
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                height: 30 * root.globalScaleFactor
                }

                TextField
                {
                width: (settingsContent.width-parent.spacing) * 4 / 5 ;
                horizontalAlignment: Text.AlignRight
                id: portTextField
                objectName: "portTextField"
                style: textfieldStyle
                height: textFieldHeight
                }
            }

            PlayerButton
            {
                objectName: "settingsDialog"
                signal connectTo(var ip, var port)
                height: textFieldHeight
                width: height
                iconScale: 0.5
                smooth:true
                opacity: 0.7
                icon1: "resources/check-inv.png"
                toggle: false
                onButtonClicked: {dialogController.showSettings(false); connectTo(hostTextField.text, portTextField.text); }
                x: parent.width - width - (10 * root.globalScaleFactor)
            }

        }
    }
}
