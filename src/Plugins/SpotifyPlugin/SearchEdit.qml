import QtQuick 2.0

Rectangle
{
    color:"transparent"

    property alias text: edit.text


    BorderImage
    {
        id: name
        source: edit.focus?"qrc:/border_images/search_active" :"qrc:/border_images/search"
        height: 16
        border.left: 30;
        border.right: 4; border.bottom: 4
        anchors.bottomMargin: 8
        anchors.fill: parent
        TextInput
        {
            id:edit
            color:"black"
            anchors.fill:  parent
            anchors.topMargin: 3
            anchors.leftMargin: 30
        }

    }

    width: 100
    height: 15
}
/*
border-image:url(:border_images/Ressources/search_edit.png) 4 4 4 30;
border-width:4px;
border-left:30px;
color: #FFFFFF;
height: 15px;*/
