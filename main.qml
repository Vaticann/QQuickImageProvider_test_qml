import QtQuick 2.15
import QtTest 1.0
import QtQuick.Window 2.15
import CameraManagerModel 1.0



// TestCase {
//     name: "main"

//     function test_case1() {
//         compare(1 + 1, 2, "sanity check");
//         verify(true);
//     }
// }

Window {
    visible: true
    width: 640; height: 480
    Image {
                id: cameraImage
                anchors.fill: parent

                source: "file:/home/firefly/boot.png" // 这样能显示图片
                // source: "image://camera" 
                fillMode: Image.PreserveAspectFit // 保持纵横比
                cache: false  // 不缓存

                onStatusChanged: {
                    console.log("Camera image status:", status)
                    // 1: Loading, 2: Ready, 3: Error, 0: Null
                }

                // onError: {
                //     console.log("Camera image error:", errorString)
                // }
            }

            Connections {
                target: CameraManagerModel
                function onFrameReady() {      // frameReady 是信号，这里是触发这个信号时，执行的函数。每一帧数据准备好时触发
                    // 强制刷新
                    cameraImage.source = ""
                    cameraImage.source = "image://camera/current" 
                }
            }



            // 启动时开始拉流
            Component.onCompleted: {
                // CameraManagerModel.startStream("http://192.168.110.8/webcam/?action=snapshot")
                CameraManagerModel.startStream("http://192.168.110.8/webcam/?action=stream")
                console.log("开始拉流1111")
            }

    // 1. 255x255矩形
// 2. 圆角50
// 3. 背景带模糊的透明
// 4. 左上角边框有渐变高光

        ShiningRectangle {
            id: shiningRect
            anchors.centerIn: parent
            width: 255
            height: 255
        }

}

