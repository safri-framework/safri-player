
import QtQuick 2.1
import QtQuick.Controls.Styles 1.0
import QtQuick.Controls 1.0






Rectangle {


    onVisibleChanged:
    {
        if(visible)
        {
            opacityAnimation.to = 0.8
            opacityAnimation.start();
            heightAnimation.to = settingsView.height / 3
           heightAnimation.start()
        }
        else
        {
            opacityAnimation.to = 0
            opacityAnimation.start();
            heightAnimation.to = -settings.height
            heightAnimation.start()
        }
    }


    PropertyAnimation
    {
        id:opacityAnimation
        duration: 300
        target: overlay
        property: "opacity"
        to: 0.8
    }

    PropertyAnimation
    {
        id:heightAnimation
        duration: 500
        target: settings
        property: "y"
        to: settingsView.height / 3
        easing.type:  Easing.OutBounce
    }


    property Component textfieldStyle:  TextFieldStyle {
        id:textFieldStyle
       textColor: "white"
       background: BorderImage {
           y: root.globalScaleFactor < 1 ? -2 : 0
           id: name
           source: "resources/lineEdit.png"
           /*border.left:0; border.top:0
           border.right: 5*root.globalScaleFactor; border.bottom: 5*root.globalScaleFactor*/
           z:-1

       }
       font.pixelSize:  root.globalScaleFactor  < 0.6 ? 12 : root.globalScaleFactor * 18;


    }



    property int textFieldHeight: root.globalScaleFactor  < 0.6 ? 20 : root.globalScaleFactor * 30;
    height: view.height
    width: view.width
    id: settingsView
    color:"transparent"



    Rectangle
    {
        id: overlay
        anchors.fill: parent
        color:"black"
        opacity:0.6
        MouseArea
        {
          anchors.fill: parent;
          onClicked: settingsView.visible = false
        }
    }

    Rectangle
    {

        MouseArea{anchors.fill:  parent}
    width: parent.width * 2/3
    height: 3*textFieldHeight + 60 * root.globalScaleFactor//*root.globalScaleFactor
    //anchors.centerIn:  parent
    anchors.horizontalCenter: parent.horizontalCenter
    y: -height


    id: settings
    border.width: 1
    border.color: "black"
    radius: 10 * root.globalScaleFactor
    color:"#1B1B1B"

    opacity: y / (settingsView.height/3)
    Rectangle
    {
        color:"transparent"
        width: settings.width - 20 * root.globalScaleFactor
        height: settings.height - 20 * root.globalScaleFactor
        x: 10 * root.globalScaleFactor
        y: 10 * root.globalScaleFactor
        id:settingsContent

            Column{
                    spacing: 20 * root.globalScaleFactor

                Row{
                    spacing: 20 * root.globalScaleFactor
                    Label
                    {

                        width: (settingsContent.width-parent.spacing) / 5;
                        text: "IP"
                        color: "white"
                        horizontalAlignment: Text.AlignRight
                        id: ipLabel
                        height: 30 * root.globalScaleFactor
                        verticalAlignment:  Text.AlignVCenter
                    }
                    TextField
                    {
                        width: (settingsContent.width-parent.spacing) * 4 / 5;
                        horizontalAlignment: Text.AlignRight
                        id:portLabel
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
                        verticalAlignment:  Text.AlignVCenter
                        height: 30 * root.globalScaleFactor
                    }
                    TextField
                    {
                        width: (settingsContent.width-parent.spacing) * 4 / 5  ;
                        horizontalAlignment: Text.AlignRight
                        style: textfieldStyle
                        height: textFieldHeight
                    }
                }




                    PlayerButton
                    {
                        height: textFieldHeight
                        width: height
                        iconScale: 0.5
                        smooth:true
                        opacity: 0.7
                        icon1: "resources/check-inv.png"
                        toggle: false
                        x: parent.width - width - (10 * root.globalScaleFactor)
                    }

            }


        }
    }
}
