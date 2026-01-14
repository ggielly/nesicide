#!/bin/bash

# Build script for 64-bit compilation

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
if [ ! -f "deps/rtmidi/librtmidi.a" ] && [ ! -f "deps/rtmidi/debug/librtmidi.a" ] && [ ! -f "deps/rtmidi/release/librtmidi.a" ]; then
    echo "Building RtMidi library..."
    cd deps/rtmidi
    qmake rtmidi.pro
    make
    cd "$ORIGINAL_DIR"
fi

# Build QHexEdit2 if not already built
if [ ! -f "deps/qhexedit2/src/libqhexedit.so" ] && [ ! -f "deps/qhexedit2/lib/libqhexedit.so" ]; then
    echo "Building QHexEdit2 library..."
    cd deps
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
if [ ! -f "deps/qscintilla2/src/libqscintilla2_qt5.so" ]; then
    echo "Building QScintilla2 library..."
    cd deps/qscintilla2/src
    qmake qscintilla.pro CONFIG+=staticlib
    make
    cd "$ORIGINAL_DIR"
fi

# Copy source files to build directories if they don't exist
echo "Preparing build directories..."
if [ ! -f "build/ide/nesicide.pro" ]; then
    echo "Copying IDE source files to build directory..."
    mkdir -p build/ide
    cp -r ../apps/ide/* ./build/ide/
    # Copy the project file specifically
    cp ../apps/ide/nesicide.pro ./build/ide/
fi

if [ ! -f "build/nes-emulator/nesicide-emulator.pro" ]; then
    echo "Copying NES Emulator source files to build directory..."
    mkdir -p build/nes-emulator
    cp -r ../apps/nes-emulator/* ./build/nes-emulator/
    cp ../apps/nes-emulator/nesicide-emulator.pro ./build/nes-emulator/
fi

if [ ! -f "build/famitracker-qt/src/famitracker-qt.pro" ]; then
    echo "Copying FamiTracker-Qt source files to build directory..."
    mkdir -p build/famitracker-qt/src
    cp -r ../apps/famitracker-qt/src/* ./build/famitracker-qt/src/
    cp ../apps/famitracker-qt/src/famitracker-qt.pro ./build/famitracker-qt/
fi

# Skipping FamiPlayer setup due to dependency on problematic famitracker library
# if [ ! -f "build/famiplayer/famiplayer.pro" ]; then
#     echo "Copying FamiPlayer source files to build directory..."
#     mkdir -p build/famiplayer
#     cp -r ../apps/famiplayer/* ./build/famiplayer/
#     cp ../apps/famiplayer/famiplayer.pro ./build/famiplayer/
# fi

# Build with 64-bit flags explicitly
echo "Building NES Emulator with 64-bit architecture..."
( cd build/nes-emulator && qmake nesicide-emulator.pro -spec linux-g++ "QMAKE_CFLAGS+=-m64" "QMAKE_CXXFLAGS+=-m64" "QMAKE_LFLAGS+=-m64" CONFIG+=debug && make )

echo "Building FamiTracker-Qt with 64-bit architecture..."
( cd build/famitracker-qt/src && qmake famitracker-qt.pro -spec linux-g++ "QMAKE_CFLAGS+=-m64" "QMAKE_CXXFLAGS+=-m64" "QMAKE_LFLAGS+=-m64" CONFIG+=debug && make )

echo "Skipping NESICIDE and FamiPlayer builds due to dependency on problematic famitracker library..."
( cd build/ide && qmake nesicide.pro -spec linux-g++ "QMAKE_CFLAGS+=-m64" "QMAKE_CXXFLAGS+=-m64" "QMAKE_LFLAGS+=-m64" CONFIG+=debug && make )
# ( cd build/famiplayer && qmake famiplayer.pro -spec linux-g++ "QMAKE_CFLAGS+=-m64" "QMAKE_CXXFLAGS+=-m64" "QMAKE_LFLAGS+=-m64" CONFIG+=debug && make )

exit 0