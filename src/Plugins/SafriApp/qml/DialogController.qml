
import QtQuick 2.1
import QtQuick.Controls.Styles 1.0
import QtQuick.Controls 1.0






Rectangle {

    property bool setVisible: false;
    property var dialog: error ;
    property bool settingsVisible: false;
    property bool errorVisible: false;
    objectName: "dialogController";

    function showError(msg)
    {
       // setVisible = false;
        dialog = error;
        setVisible = true;
        dialog.errorMsg = msg
        console.log(msg)
        errorVisible = true;
    }

    function hideError()
    {
        setVisible = false;
        errorVisible = false;
    }

    function showSettings(visible)
    {
        if(settingsVisible == visible)
        return;

        if(visible)
        {
           // setVisible = false;
            dialog = settings;
            setVisible = true;
            settingsVisible = true;
        }
        else
        {

           setVisible = false;
           settingsVisible = false;
        }
    }
    onSetVisibleChanged:
    {
        if(setVisible)
        {
            visible = true;
            opacityAnimation.to = 0.8
            heightAnimation.to = dialogController.height / 3
            if(animations.running)
                animations.complete()
           animations.start()
        }
        else
        {
            opacityAnimation.to = 0
            heightAnimation.to = -dialog.height
            if(animations.running)
                animations.complete()
           animations.start()
        }
    }

    ParallelAnimation
    {
        id:animations;


        PropertyAnimation
        {
            id:opacityAnimation
            duration: 300
            target: overlay
            property: "opacity"
            to: 0.8
            onStopped: if(!setVisible)dialogController.visible = false;
        }

        PropertyAnimation
        {
            id:heightAnimation
            duration: 500
            target: dialog
            property: "y"
            to: dialogController.height / 3
            easing.type:  Easing.OutBounce
        }
    }

    property Component textfieldStyle:  TextFieldStyle {
        id:textFieldStyle
       textColor: "white"
       background: BorderImage {
           y: root.globalScaleFactor < 1 ? -2 : 0
           id: name
           source: "resources/lineEdit.png"

           z:-1

       }
       font.pixelSize:  root.globalScaleFactor  < 0.6 ? 12 : root.globalScaleFactor * 18;
    }



    property int textFieldHeight: root.globalScaleFactor  < 0.6 ? 20 : root.globalScaleFactor * 30;
    height: view.height
    width: view.width
    id: dialogController
    color:"transparent"


    SettingsDialog{id: settings; z: 100}
    ErrorDialog{id: error; z: 100}

    Rectangle
    {
        id: overlay
        anchors.fill: parent
        color:"black"
        opacity:0.6
        MouseArea
        {
          anchors.fill: parent;
          onClicked: {dialogController.visible = false; setVisible = false}
        }
    }


}
