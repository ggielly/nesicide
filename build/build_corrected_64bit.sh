#!/bin/bash

# Corrected build script for nesicide IDE compilation on 64-bit Linux

echo "Setting up environment for nesicide IDE compilation..."
echo "====================================================="

# Save current directory to return to it later
ORIGINAL_DIR=$(pwd)

# Ensure dependencies are built
echo "Checking dependencies..."

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

# Prepare build directories with correct paths
echo "Preparing build directories..."

# Create build directory structure
mkdir -p build/ide
mkdir -p build/nes-emulator
mkdir -p build/famitracker-qt/src
mkdir -p build/famiplayer

# Copy source files to build directories
echo "Copying source files to build directories..."

# Copy IDE source files
if [ ! -f "build/ide/nesicide.pro" ]; then
    echo "Copying IDE source files..."
    cp -r apps/ide/* build/ide/
    cp apps/ide/nesicide.pro build/ide/
fi

# Copy NES Emulator source files
if [ ! -f "build/nes-emulator/nesicide-emulator.pro" ]; then
    echo "Copying NES Emulator source files..."
    cp -r apps/nes-emulator/* build/nes-emulator/
    cp apps/nes-emulator/nesicide-emulator.pro build/nes-emulator/
fi

# Copy FamiTracker-Qt source files (this is the working version)
if [ ! -f "build/famitracker-qt/src/famitracker-qt.pro" ]; then
    echo "Copying FamiTracker-Qt source files..."
    cp -r apps/famitracker-qt/src/* build/famitracker-qt/src/
    cp apps/famitracker-qt/src/famitracker-qt.pro build/famitracker-qt/
fi

# Copy FamiPlayer source files
if [ ! -f "build/famiplayer/famiplayer.pro" ]; then
    echo "Copying FamiPlayer source files..."
    cp -r apps/famiplayer/* build/famiplayer/
    cp apps/famiplayer/famiplayer.pro build/famiplayer/
fi

# Build with 64-bit flags
echo "Building nesicide components with 64-bit architecture..."

echo "Building IDE..."
( cd build/ide && qmake nesicide.pro -spec linux-g++ "QMAKE_CFLAGS+=-m64" "QMAKE_CXXFLAGS+=-m64" "QMAKE_LFLAGS+=-m64" CONFIG+=debug DEFINES-=QTMFC_LIBRARY && make )

echo "Building NES Emulator..."
( cd build/nes-emulator && qmake nesicide-emulator.pro -spec linux-g++ "QMAKE_CFLAGS+=-m64" "QMAKE_CXXFLAGS+=-m64" "QMAKE_LFLAGS+=-m64" CONFIG+=debug && make )

echo "Building FamiTracker-Qt..."
( cd build/famitracker-qt/src && qmake famitracker-qt.pro -spec linux-g++ "QMAKE_CFLAGS+=-m64" "QMAKE_CXXFLAGS+=-m64" "QMAKE_LFLAGS+=-m64" CONFIG+=debug && make )

echo "Building FamiPlayer..."
( cd build/famiplayer && qmake famiplayer.pro -spec linux-g++ "QMAKE_CFLAGS+=-m64" "QMAKE_CXXFLAGS+=-m64" "QMAKE_LFLAGS+=-m64" CONFIG+=debug && make )

echo ""
echo "Build process completed!"
echo "========================"
echo "IDE executable: build/ide/debug/nesicide (if successful)"
echo "FamiTracker-Qt executable: build/famitracker-qt/src/famitracker"
echo "NES Emulator executable: build/nes-emulator/debug/nesicide-emulator"
echo "FamiPlayer executable: build/famiplayer/debug/famiplayer"