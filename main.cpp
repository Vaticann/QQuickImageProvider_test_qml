#include <QtQuickTest/quicktest.h>
#include <QQmlApplicationEngine>
#include "imageprovider.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.addImageProvider("camera", new ImageProvider());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}







QUICK_TEST_MAIN(example)
