#-------------------------------------------------
#
# Project created by QtCreator 2016-07-06T21:53:37
#
#-------------------------------------------------
QT       += core gui
include(xlsx/qtxlsx.pri)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = xml_parse_doc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tinyxml/tinystr.cpp \
    tinyxml/tinyxml.cpp \
    tinyxml/tinyxmlerror.cpp \
    tinyxml/tinyxmlparser.cpp

HEADERS  += mainwindow.h \
    tinyxml/tinystr.h \
    tinyxml/tinyxml.h

FORMS    += mainwindow.ui
