import QtQuick 2.0
import QtQuick.Layouts 1.0

Rectangle {
    id:root
    width: 100
    height: 62
    default property alias content: layout.children
    anchors.fill: parent
    color:"transparent"
    property int spacing:10
    property int allItems: layout.children.length
    property int dynamicItems:0
    property int dynamicHeight//: dynamicItems > 0 ? availableSpace / dynamicItems : 0
   // property int availableSpace: height-fullFixHeight
    property int fullFixHeight: 0

    onHeightChanged: calcDynamicHeight()
    onDynamicHeightChanged:
    {
        for(var n = 0; n < layout.children.length; n++)
        {
           if(!layout.children[n].fixHeight && layout.children[n].expanded)
               layout.children[n].expandedHeight = dynamicHeight
        }
    }

    Component.onCompleted:
    {
        for(var i = 0; i < layout.children.length; i++)
        {
           layout.children[i].expandChanged.connect(childExpandedChanged)
           layout.children[i].index = i
        }
        calcDynamicHeight()
    }

    function calcDynamicHeight()
    {
        var fullFixHeight = 0;
        var dynamicExpandedItems = 0
        for(var i = 0; i < layout.children.length; i++)
        {
            if(layout.children[i].expanded)
            {
                if(layout.children[i].fixHeight)
                {
                    fullFixHeight += layout.children[i].expandedHeight
                }
                else
                {
                    dynamicExpandedItems++
                }
            }
            else
            {
                fullFixHeight += 30
            }
        }

        fullFixHeight += (layout.children.length -1) * spacing

        root.dynamicHeight = (root.height - fullFixHeight) /dynamicExpandedItems

    }

    function childExpandedChanged(expanded, index)
    {
        calcDynamicHeight()
        layout.children[index].reallyExpanded = expanded
    }

    Column
    {
        spacing: root.spacing
        anchors.fill: parent
        id: layout
    }
}
