import QtQuick 2.0

Rectangle {

    width: view.width; height: view.height
    color: "#272727"
    id:view1
    Rectangle
    {
        width: view.width - 20  * root.globalScaleFactor
        height:player.online ? view.height - 20 *root.globalScaleFactor : view.height - 30 * root.globalScaleFactor - treeMenu.height
        radius: 10 * root.globalScaleFactor
        x:10 * root.globalScaleFactor;
        y:10 * root.globalScaleFactor;
        color:"#1B1B1B"
        TreeView
        {
            clip:true
            anchors.top: currentItemRect.bottom
            anchors.bottom:  parent.bottom
            color: "transparent"
            id: treeView
            objectName: "treeView"
            onCurrentItemTextChanged:
            {
                if(currentItemText =="")
                {
                    currentItemRect.height = 0;
                    currentItemRect.opacity = 0.1
                }
                else
                {
                    currentItemRect.height = root.globalScaleFactor > 0.7 ? 40 * root.globalScaleFactor : 30;
                    currentItemRect.opacity =1
                }
                currentItemRectText.text = currentItemText;
            }
        }

        Rectangle
        {

          x:0;
          y:0;
          width: parent.width;
          height: 0;
          opacity: 0.1;
          color: "transparent"
          id: currentItemRect

          BorderImage {
              id: name
              source: "resources/labelbackground.png"
              width: 100; height: 100
              border.left: 5; border.top: 5
              border.right: 5; border.bottom: 5
              anchors.fill: parent
          }


          Text
          {
              color: "#FFFEFE"
              anchors.centerIn: parent
              id: currentItemRectText
              Text
              {
                  x:2
                  y:2
                  opacity:0.5
                  color: "black"
                  anchors.centerIn: parent
                  id: textShadow
                  text: parent.text
              }
          }

          MouseArea
          {
            anchors.fill:  parent
            onClicked: treeView.prevIndex();
          }

          Behavior on height { PropertyAnimation {duration:250; easing.type: Easing.OutQuad }}
          Behavior on opacity { PropertyAnimation {duration:250; }}


        }
    }
    Rectangle
    {
        id:treeMenu
        visible: !player.online
        x:10 * root.globalScaleFactor;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 10 * root.globalScaleFactor;
        height: 45 * root.globalScaleFactor;
        width: parent.width - 20 * root.globalScaleFactor
        radius: 10 * root.globalScaleFactor
        color:"#1B1B1B"

        Rectangle
        {
            color: "transparent"
            width: treeMenu.width / 3
            height: treeMenu.height
            x:0
            y:0
            PlayerButton
            {
                width: parent.width
                height: parent.height
                checkable: true
                iconScale:1.2
                icon1: "resources/genre.png"
                objectName: "genreButton";
                id: genreButton
                onButtonClicked: {albumButton.enabled = false; artistButton.enabled = false}
            }
        }
        Rectangle
        {
            width: treeMenu.width / 3
            height: treeMenu.height
            color: "transparent"
            x:(treeMenu.width / 3) * 1
            y:0
            PlayerButton
            {
                id: artistButton;
                width: parent.width
                height: parent.height
                checkable: true
                iconScale: 1.2
                //enabled: true
                icon1: "resources/artist.png"
                objectName: "artistButton";
                onButtonClicked: {albumButton.enabled = false; genreButton.enabled = false}
            }
        }
        Rectangle
        {
            width: treeMenu.width / 3
            height: treeMenu.height
            color: "transparent"
            x:(treeMenu.width / 3) * 2
            y:0
            PlayerButton
            {
                id:albumButton
                width: parent.width
                height: parent.height
                icon1: "resources/album.png"
                iconScale: 1.2
                checkable: true
                objectName: "albumButton";
                onButtonClicked: {artistButton.enabled = false; genreButton.enabled = false}
            }
        }

    }
}





