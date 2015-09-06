import QtQuick 2.2
import QtQuick.Dialogs 1.0
import Qt.labs.folderlistmodel 1.0

Rectangle {
    id: coverView
    width:view.width; height:view.height
    color: "black"
    visible: true
    property int highestZ: 0
    property real defaultSize: 200
    clip:true;
    objectName: "coverView"
    function setFolder(path)
    {
        folderModel.folder = path;
    }

    Repeater {
        model: FolderListModel {

            id: folderModel
            objectName: "folderModel"
            showDirs: false
            nameFilters: ["*.png", "*.jpg", "*.gif"]
           // folder:  "file:/home/frime/.local/share/Safri-Player/Assets/AlbumCoversHires/"

        }
        Rectangle {
            id: photoFrame
            width: image.width * image.scale + 20
            height: image.height * image.scale + 20
            border.color: "black"
            border.width: 2
            smooth: true
            antialiasing: true
            x: Math.random() * coverView.width - defaultSize
            y: Math.random() * coverView.height - defaultSize
            rotation: Math.random() * 13 - 6
            Image {
                id: image
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
                source: folderModel.folder + fileName
                scale: defaultSize / Math.max(sourceSize.width, sourceSize.height)
                antialiasing: true
               // visible: rot.angle < 90 ? true : false;
                transform:
                Rotation
                {
                    id: rot
                    origin.x:image.width/2;
                    origin.y:image.height/2;
                    axis.x:0; axis.y:1; axis.z:0
                    angle:0
                    Behavior on angle { PropertyAnimation{duration: 1000; easing.type: Easing.InOutCubic} }
                }


            }
            PinchArea {
                anchors.fill: parent
                pinch.target: photoFrame
                pinch.minimumRotation: -360
                pinch.maximumRotation: 360
                pinch.minimumScale: 0.1
                pinch.maximumScale: 10
                onPinchFinished: photoFrame.border.color = "black";
                MouseArea {
                    onPressed: {view.interactive = false; photoFrame.z = ++coverView.highestZ;}
                    onReleased: view.interactive = true
                    onClicked: rot.angle = (rot.angle + 180) % 360
                    id: dragArea
                    hoverEnabled: true
                    anchors.fill: parent
                    drag.target: photoFrame
                    onEntered: photoFrame.border.color = "red";
                    onExited: photoFrame.border.color = "black";
                    onWheel: {
                        if (wheel.modifiers & Qt.ControlModifier) {
                            photoFrame.rotation += wheel.angleDelta.y / 120 * 5;
                            if (Math.abs(photoFrame.rotation) < 4)
                                photoFrame.rotation = 0;
                        } else {
                            photoFrame.rotation += wheel.angleDelta.x / 120;
                            if (Math.abs(photoFrame.rotation) < 0.6)
                                photoFrame.rotation = 0;
                            var scaleBefore = image.scale;
                            image.scale += image.scale * wheel.angleDelta.y / 120 / 10;
                            photoFrame.x -= image.width * (image.scale - scaleBefore) / 2.0;
                            photoFrame.y -= image.height * (image.scale - scaleBefore) / 2.0;
                        }
                    }
                }
            }
        }
    }


  //  Component.onCompleted: fileDialog.open()
}
