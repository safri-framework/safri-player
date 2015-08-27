import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle
{
    id:root
    color:"transparent"
    width: parent.width
    Layout.fillWidth: true
    Layout.minimumHeight: height
    Layout.maximumHeight: height
    height: fullHeight//layoutwrapper.height + 30
    property alias text: label.text
    default property alias content: layout.children
    property alias expanded: p.contentVisible
    property string icon: "qrc:/icons/artist"
    property int fullHeight: 0
    onFullHeightChanged: content[0].height = fullHeight-30
    onContentChanged: fullHeight =  content[0].height+30
    signal expandChanged(bool expanded)
    property bool fixHeight: false

   // property var layoutWrapper: layoutwrapper
    QtObject
    {
        id:p
        property int animationDuration: 200
        property bool contentVisible:  true;
    }

    Rectangle
    {
        id: control
        color: "transparent"
        Layout.fillWidth: true
        width: parent.width
        height: 30


        MouseArea
        {
            anchors.fill: parent
            onClicked: {p.contentVisible = !p.contentVisible; root.expandChanged(p.contentVisible)}
        }


        Rectangle
        {
            id: icon
            width: 30
            height: 30
            color:"transparent"
            anchors.right: parent.right
            Image
            {
                anchors.centerIn: parent
                source: root.icon
            }
        }


        RowLayout
        {
            spacing: 0
            Rectangle
            {
                id: triangleIcon
                width: 30
                height: 30
                visible: root.icon
                color:"transparent"
                Image
                {
                    anchors.centerIn: parent
                    source: "qrc:/icons/triangleIndication"
                }
            }


            Text
            {
                id:label
                color: "white"
                height: parent.height
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle
        {
            height: 1
            anchors.bottom: parent.bottom
            width: parent.width
            color:"#4b6e87"
        }
    }

    states:
    [
        State
        {
            name:"collapsed"
            when: !p.contentVisible
            PropertyChanges { target:layoutwrapper; height:0}
            PropertyChanges { target: root; height: 30}
            PropertyChanges { target: layoutwrapper; implicitHeight:0}
          //  PropertyChanges { target:layoutwrapper; fillHeight:false}
            PropertyChanges { target: layoutwrapper; opacity:0}
            PropertyChanges { target:  triangleIcon; rotation:-90}
        }
    ]

    transitions:
    [
        Transition {
            NumberAnimation
            {

                duration: p.animationDuration                
                properties: "height,rotation,implicitHeight,opacity"
                easing.type: Easing.OutQuad
            }}
    ]

    Rectangle
    {
        clip:true
        anchors.top: control.bottom
        id: layoutwrapper
        height: fullHeight-30//content[0].height
        width:control.width
        color:"transparent"
        ColumnLayout
        {
            width: parent.width
            id:layout
            visible: true
        }
    }
}
