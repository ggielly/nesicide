#-------------------------------------------------
#
# Project created by QtCreator 2015-08-08T12:58:45
#
#-------------------------------------------------

QT       -= core gui

TARGET = rtmidi
TEMPLATE = lib

TOP = ../..

CONFIG(release, debug|release) {
   DESTDIR = release
} else {
   DESTDIR = debug
}
CONFIG+=c++11

OBJECTS_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
RCC_DIR = $$DESTDIR
UI_DIR = $$DESTDIR

DEFINES += RTMIDI_LIBRARY

win32:DEFINES += __WINDOWS_MM__
macx:DEFINES += __MACOSX_CORE__
unix:!macx:DEFINES += __LINUX_ALSA__

SOURCES += RtMidi.cpp

HEADERS += RtMidi.h

win32:LIBS += -lwinmm
macx:LIBS +=  -framework CoreMIDI -framework CoreFoundation -framework CoreAudio
unix:!macx {
   LIBS += $$system(pkg-config alsa --libs)
   QMAKE_CXXFLAGS += $$system(pkg-config alsa --cflags)
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
