import QtQuick 2.12
import QtGraphicalEffects 1.0

Item {
    id: root
    width: 255
    height: 255

    // 可调透明度
    property real rectOpacity: 0.7
    // 可调模糊程度
    property real blurRadius: 16

    // 背景内容（可根据需要替换为实际内容）
    Rectangle {
        anchors.fill: parent
        color: "#ffffff"
        visible: false // 仅用于演示毛玻璃效果
    }

    // 高斯模糊
    GaussianBlur {
        id: blur
        anchors.fill: parent
        source: ShaderEffectSource {
            sourceItem: parent
            hideSource: true
        }
        radius: blurRadius
        samples: 32
        transparentBorder: true
    }

    // 圆角遮罩
    OpacityMask {
        id: mask
        anchors.fill: parent
        source: blur
        maskSource: Rectangle {
            width: 255
            height: 255
            radius: 50
            color: "white"
        }
        opacity: rectOpacity
    }

    // 边框
    Rectangle {
        width: 255
        height: 255
        radius: 50
        color: "transparent"
        border.color: "#cccccc"
        border.width: 1
        anchors.centerIn: parent
        z: 1
    }
}
