#-------------------------------------------------
#
# Project created by QtCreator 2013-09-06T23:20:03
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UIDesigner
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qabstracttreemodel.cpp \
    qtreeitem.cpp \
    qccnode.cpp \
    qscene.cpp \
    qpropertybrowser.cpp \
    qstoragedata.cpp \
    qdataparser.cpp \
    qselectsizedialog.cpp

HEADERS  += mainwindow.h \
    qabstracttreemodel.h \
    qtreeitem.h \
    qccnode.h \
    qdefine.h \
    qscene.h \
    qpropertybrowser.h \
    qstoragedata.h \
    qdataparser.h \
    qselectsizedialog.h

FORMS    += mainwindow.ui \
    qselectsizedialog.ui

include(extension/extension.pri)
include(qtpropertybrowser/qtpropertybrowser.pri)
