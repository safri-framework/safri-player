// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle
{
    property string icon1: "images/ico_play.png"
    property string icon2:  "images/ico_pause.png"
    property bool enabled: true
    property bool playing: false
    property bool toggle: true


    id: button
    width: parent.width / 5
    height: parent.height
    color:"transparent"



    Image {
        id: buttonIcon
        smooth:true
        source: if(!button.playing)
                    button.icon1
                else
                    button.icon2
        anchors.centerIn: parent
        opacity: if(!button.enabled)
                     0.5
                 else
                     1
    }

    MouseArea
    {
        width:parent.width
        height: parent.height
        onClicked:
            if(button.toggle)
            {
                if(button.enabled)
                {
                    if(button.playing)
                    {
                        buttonIcon.source = button.icon1
                        button.playing = false;
                    }
                    else
                    {
                       buttonIcon.source =button.icon2
                        button.playing = true;
                    }

                }
            }
            else
            {
                console.log("nix")
            }

        onPressedChanged: if(pressed && button.enabled)
                          buttonIcon.scale = 1.3
                         else
                            buttonIcon.scale = 1

        }
}

