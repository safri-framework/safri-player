import QtQuick 2.0

Rectangle
{
    color:"transparent";
    anchors.centerIn: parent
    height:parent.height
    width:parent.width
    id: main
    property ListView currentView: viewA
    property ListView nextView: viewB
    property var nextModelIndex


    function nextIndex(index)
    {

        nextModelIndex = index
        nextAnimation.start()

    }



    function prevIndex()
    {
        currentView.model.rootIndex = currentView.model.parentModelIndex()
    }

    Rectangle
    {
        color:"transparent"
        id: viewRect
        x:0
        y:0
        width: main.width
        height: main.height
        smooth: true

    ListView
    {
        anchors.centerIn: parent
        width: parent.width
        height:parent.height

        id: viewA
        model: musicQMLModel
        interactive: true




        ParallelAnimation
        {
            id: nextAnimation
            onRunningChanged:
            {
                if (!nextAnimation.running)
                {
                    viewA.model.rootIndex = nextModelIndex
                    viewRect.x = 0
                    viewRect.opacity = 1
                }
            }

            NumberAnimation
            {
                duration: 300
                target: viewRect
                properties: "opacity"
                from: 1
                to: 0

            }


            NumberAnimation
            {

                duration: 300
                target: viewRect
                properties: "x"
                from: 0
                easing.type: Easing.OutCubic
                to: -main.width

            }
        }
    }

}
}
