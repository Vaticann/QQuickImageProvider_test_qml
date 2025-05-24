CONFIG += warn_on qmltestcase

QT += quick qml

TARGET = ui_test

TEMPLATE = app

DISTFILES += \
    ShiningRectangle.qml \
    tst_main.qml

SOURCES += \
    cameramanagermodel.cpp \
    imageprovider.cpp \
    main.cpp

HEADERS += \
    cameramanagermodel.h \
    imageprovider.h

RESOURCES += main.qrc
