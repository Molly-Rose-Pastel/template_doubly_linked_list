QT += testlib
QT -= gui

CONFIG += c++17 console qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
        main.cpp


HEADERS += \
    DLinkedList.h \
    UnitTest.h

