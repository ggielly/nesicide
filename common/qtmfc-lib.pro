#-------------------------------------------------
#
# Project created for QtMFC compatibility layer
#
#-------------------------------------------------

TARGET = qtmfc
TEMPLATE = lib

QT += core \
      gui \
      widgets \
      xml \
      network

greaterThan(QT_MAJOR_VERSION, 5) {
   QT += core5compat
}

QMAKE_CFLAGS += -w -D_GNU_SOURCE=1 -D_REENTRANT
QMAKE_CXXFLAGS += -w -D_GNU_SOURCE=1 -D_REENTRANT

TOP = ..

CONFIG += warn_off

CONFIG(release, debug|release) {
   DESTDIR = release
} else {
   DESTDIR = debug
}

OBJECTS_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
RCC_DIR = $$DESTDIR
UI_DIR = $$DESTDIR

DEFINES -= UNICODE
DEFINES += NOMINMAX NULL=0

INCLUDEPATH += \
   . \
   $$TOP/common

# Define the source and header files for the QtMFC compatibility layer
SOURCES += \
    cqtmfc.cpp

HEADERS += \
    cqtmfc.h \
    afxmsg_.h

# Add the library to the destination directory
target.path = $$[QT_INSTALL_LIBS]
INSTALLS += target