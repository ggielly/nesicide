#!/bin/bash

# Check for prerequisites
if [ -f "/etc/debian_version" ]; then
   echo "Checking for required packages..."
   if ! command -v qmake &> /dev/null; then
       echo "qmake not found. Please install Qt5 development packages."
       echo "Run: sudo apt install qt5-qmake qtbase5-dev qtbase5-dev-tools libqt5opengl5-dev"
       exit 1
   fi
fi

# Ensure dependencies are built
echo "Checking dependencies..."

# Save current directory to return to it later
ORIGINAL_DIR=$(pwd)

# Build RtMidi if not already built
if [ ! -f "../deps/rtmidi/librtmidi.a" ] && [ ! -f "../deps/rtmidi/debug/librtmidi.a" ] && [ ! -f "../deps/rtmidi/release/librtmidi.a" ]; then
    echo "Building RtMidi library..."
    cd ../deps/rtmidi
    qmake rtmidi.pro
    make
    cd "$ORIGINAL_DIR"
fi

# Build QHexEdit2 if not already built
if [ ! -f "../deps/qhexedit2/src/libqhexedit.so" ] && [ ! -f "../deps/qhexedit2/lib/libqhexedit.so" ]; then
    echo "Building QHexEdit2 library..."
    cd ../deps
    if [ ! -d "qhexedit2" ]; then
        echo "Cloning QHexEdit2..."
        git clone https://github.com/Simsys/qhexedit2.git
    fi
    cd qhexedit2/src
    qmake qhexedit.pro
    make
    mkdir -p ../lib
    cp libqhexedit.so* ../lib/
    cd "$ORIGINAL_DIR"
fi

# Build QScintilla2 if not already built
if [ ! -f "../deps/qscintilla2/src/libqscintilla2_qt5.so" ]; then
    echo "Building QScintilla2 library..."
    cd ../deps/qscintilla2/src
    qmake qscintilla.pro CONFIG+=staticlib
    make
    cd "$ORIGINAL_DIR"
fi

# Copy source files to build directories if they don't exist
echo "Preparing build directories..."
if [ ! -f "ide/nesicide.pro" ]; then
    echo "Copying IDE source files to build directory..."
    cp -r ../apps/ide/* ./ide/
    # Copy the project file specifically
    cp ../apps/ide/nesicide.pro ./ide/
fi

if [ ! -f "nes-emulator/nesicide-emulator.pro" ]; then
    echo "Copying NES Emulator source files to build directory..."
    cp -r ../apps/nes-emulator/* ./nes-emulator/
    cp ../apps/nes-emulator/nesicide-emulator.pro ./nes-emulator/
fi

if [ ! -f "famitracker-qt/famitracker-qt.pro" ]; then
    echo "Copying FamiTracker-Qt source files to build directory..."
    mkdir -p ./famitracker-qt/src
    cp -r ../apps/famitracker-qt/src/* ./famitracker-qt/src/
    cp ../apps/famitracker-qt/src/famitracker-qt.pro ./famitracker-qt/
fi

if [ ! -f "famiplayer/famiplayer.pro" ]; then
    echo "Copying FamiPlayer source files to build directory..."
    cp -r ../apps/famiplayer/* ./famiplayer/
    cp ../apps/famiplayer/famiplayer.pro ./famiplayer/
fi

# add CONFIG+=debug to qmake to build debug.
echo Building NESICIDE...
( cd ide && qmake nesicide.pro -spec linux-g++ CONFIG+=debug && make QSCINTILLA_NAME=qscintilla2_qt5 QHEXEDIT_NAME=qhexedit )
echo Building NES Emulator...
( cd nes-emulator && qmake nesicide-emulator.pro -spec linux-g++ CONFIG+=debug && make )
echo Building FamiTracker-Qt...
( cd famitracker-qt/src && qmake famitracker-qt.pro -spec linux-g++ CONFIG+=debug && make )
echo Building FamiPlayer...
( cd famiplayer && qmake famiplayer.pro -spec linux-g++ CONFIG+=debug && make )

exit 0
