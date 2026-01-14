#!/bin/bash

echo "Building nesicide with working components..."
echo "============================================="

# Save current directory to return to it later
ORIGINAL_DIR=$(pwd)

# Ensure dependencies are built
echo "Checking dependencies..."

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

# Build with 64-bit flags explicitly
echo "Building NES Emulator with 64-bit architecture..."
( cd build/nes-emulator && qmake nesicide-emulator.pro -spec linux-g++ "QMAKE_CFLAGS+=-m64" "QMAKE_CXXFLAGS+=-m64" "QMAKE_LFLAGS+=-m64" CONFIG+=debug && make )

echo "Building FamiTracker-Qt with 64-bit architecture..."
( cd build/famitracker-qt/src && qmake famitracker-qt.pro -spec linux-g++ "QMAKE_CFLAGS+=-m64" "QMAKE_CXXFLAGS+=-m64" "QMAKE_LFLAGS+=-m64" CONFIG+=debug && make )

echo "FamiTracker-Qt built successfully!"
echo "To run FamiTracker-Qt: ./build/famitracker-qt/src/famitracker"
echo ""
echo "NES Emulator built successfully!"
echo "To run NES Emulator: ./build/nes-emulator/nesicide-emulator"