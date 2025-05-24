#include <QtQuickTest/quicktest.h>
#include <QQmlApplicationEngine>
#include "imageprovider.h"
#include "cameramanagermodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterSingletonType<CameraManagerModel>("CameraManagerModel", 1, 0, "CameraManagerModel"                                                              ,
                                               [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject* {
                                                   (void)engine;
                                                   (void)jsEngine;
                                                   return &CAMERA_MANAGER_MODEL;
                                               }
                                               );

    engine.addImageProvider("camera", new ImageProvider());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}







// QUICK_TEST_MAIN(example)
