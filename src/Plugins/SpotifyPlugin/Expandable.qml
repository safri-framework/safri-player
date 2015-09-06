import QtQuick 2.2
import QtQuick.Layouts 1.1
import "Helpers.js" as Helpers
Rectangle
{
    id:root
    color:expanded? Helpers.transparentColor("000000",8) :"transparent"
    width: parent.width


    property alias text: label.text
    default property alias content: layout.children
    property alias expanded: p.expanded
    property string icon: "qrc:/icons/artist"
    property int expandedHeight
    property bool fixHeight: false
    signal expandChanged(bool expanded, int index)
    property int index
    Behavior on height{NumberAnimation{easing.type: Easing.OutQuad; duration:p.animationDuration}}
    property alias reallyExpanded: p.reallyExpaneded
   // property var layoutWrapper: layoutwrapper

    NumberAnimation
    {
        id: heightAnimation
        duration: p.animationDuration
    }

    function expandTo(height)
    {
        p.contentVisible = true
    }



    QtObject
    {
        id:p
        property int animationDuration: 200
        property bool expanded:true
        property bool reallyExpaneded: true
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
            onClicked:
            {p.expanded = !p.expanded; root.expandChanged(p.expanded, index)}
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
            name:"open"
            when: p.reallyExpaneded
            PropertyChanges { target:  triangleIcon; rotation:0}
            PropertyChanges { target:  root; height: root.expandedHeight}
            PropertyChanges { target: layoutwrapper; opacity:1}
        },
        State
        {
            name:"closed"
            when:!p.reallyExpaneded
            PropertyChanges { target:  triangleIcon; rotation:-90}
            PropertyChanges { target:  root; height: 30}
            PropertyChanges { target: layoutwrapper; opacity:0}
        }
    ]

    transitions:
    [
        Transition {
            NumberAnimation
            {

                duration: p.animationDuration
                properties: "height,rotation,opacity"
                easing.type: Easing.OutQuad
            }}
    ]

    Rectangle
    {
        clip:true
        anchors.top: control.bottom
        id: layoutwrapper
        height: root.height-30//content[0].height
        onHeightChanged: children[0].height = height
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
