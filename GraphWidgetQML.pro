TEMPLATE = app

QT += qml quick printsupport core gui declarative
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp \
    dataparser.cpp \
    graphitem.cpp \
    qcustomplot.cpp \
    consumerthread.cpp \
    graphwidget.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    consumerthread.h \
    dataparser.h \
    graphitem.h \
    qcustomplot.h \
    graphwidget.h
