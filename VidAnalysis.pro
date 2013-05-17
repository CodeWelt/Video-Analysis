# -------------------------------------------------
# Project created by QtCreator 2010-01-30T19:12:09
# -------------------------------------------------
TARGET = VidAnalysis
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    video.cpp
HEADERS += mainwindow.h \
    video.h
FORMS += mainwindow.ui
LIBS = /usr/lib/libavcodec.so \
    /usr/lib/libavformat.so \
    /usr/lib/libavutil.so \
    /usr/lib/libswscale.a
RESOURCES += rsc.qrc
