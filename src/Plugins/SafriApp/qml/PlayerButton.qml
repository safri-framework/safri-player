// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0


Rectangle
{
    property string icon1: "resources/playerIcon_play.png"
    property string icon2:  "resources/media-pause-inv.png"
    property bool enabled: true
    property bool playing: false
    property bool toggle: true
    property bool checkable: false;
    property double iconScale: 1

    signal buttonClicked

    onCheckableChanged:
    {
        enabled = !checkable
    }

    id: button
    width: parent.width / 5
    height: parent.height
    color:"transparent"

    onPlayingChanged:
        if(!button.playing)
        {
            buttonIcon.source = button.icon1;
        }
        else
        {
           buttonIcon.source = button.icon2;
        }


    Image {
        scale:root.globalScaleFactor * iconScale
        anchors.centerIn: parent
        id: buttonIcon
        smooth:true
        source: if(!button.playing)
                {
                    button.icon1
                }
                else
                {
                    button.icon2
                }
        opacity: if(!button.enabled)
                     0.3
                 else
                     1
    }

    MouseArea
    {
        id: mouseArea
        width:parent.width
        height: parent.height
        onClicked:
            if(button.checkable)
            {
                button.enabled = !button.enabled
                button.buttonClicked()
            }
            else
            {
                if(button.toggle)
                {
                    if(button.enabled)
                    {
                        if(button.playing)
                        {

                            button.playing = false;
                            button.buttonClicked()
                        }
                        else
                        {
                            button.playing = true;
                            button.buttonClicked()
                        }

                    }
                }
                else
                {
                    button.buttonClicked()
                    console.log("nix")
                }
            }
        onPressedChanged: if(pressed && button.enabled)
                            buttonIcon.scale = 1.2 * root.globalScaleFactor * button.iconScale;
                         else
                            buttonIcon.scale = 1 * root.globalScaleFactor * button.iconScale;

        }
}

