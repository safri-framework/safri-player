import QtQuick 2.0

Rectangle {

    width: view.width; height: view.height
    color: "#272727"
    id:view1
    Rectangle
    {
        width: view.width - 20  * root.globalScaleFactor
        height: view.height - 20 * root.globalScaleFactor
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
                    currentItemRect.height = rowHeight / 3 < 40 ? 40 : rowHeight/3;
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
}





