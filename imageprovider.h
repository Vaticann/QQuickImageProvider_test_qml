#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QImage>
#include <QDebug>


class ImageProvider : public QQuickImageProvider
{

public:

    // static ImageProvider &instance()    // 全局单例模式要有这个static
    // {
    //     static ImageProvider _instance;
    //     return _instance;
    // }

    ImageProvider();
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

    QImage _image;

};

// #define IMAGE_PROVIDER ImageProvider::instance()
#endif // IMAGEPROVIDER_H
