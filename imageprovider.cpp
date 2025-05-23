#include "imageprovider.h"




ImageProvider::ImageProvider(): QQuickImageProvider(QQuickImageProvider::Image)
{qDebug() << "ImageProvider constructed";}


// 这里的作用是：当QML需要显示图片时，调用requestImage()函数，返回当前帧图片。
QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    qDebug() << "requestImage called, id:" << id;
    qDebug() << "requestImage called";
    // QImage img = CameraManagerModel::instance().currentFrame();
    QImage img = QImage("/home/firefly/boot.png");
    qDebug() << "Current frame is null?" << img.isNull();
    // if (size)
    //     *size = img.size();
    // if (requestedSize.isValid())
    //     return img.scaled(requestedSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    return img;
}
