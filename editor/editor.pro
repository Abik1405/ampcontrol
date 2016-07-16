#-------------------------------------------------
#
# Project created by QtCreator 2015-08-12T14:57:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = ampcontroleditor
TEMPLATE = app

DEFINES += _TEA5767 _RDA580X _TUX032 _LM7001

SOURCES += main.cpp\
		mainwindow.cpp \
	lcdconverter.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
	lcdconverter.h \
    aboutdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui

RESOURCES += \
    res.qrc
