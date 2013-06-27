// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0

Rectangle {
    width: parent.width
    height: parent.height

    BorderImage {
        id: name
        source: "images/background_home.png"
        width: parent.width; height: parent.height
        border.left: 0; border.top: 0
        border.right: 0; border.bottom: 0
    }

    Behavior on opacity {
        NumberAnimation{
            duration: 500
            easing.type: Easing.OutExpo
        }
    }

}
