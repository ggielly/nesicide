#!/bin/bash

# Build script for nesicide project using CLANG instead of GCC
# This script builds the entire project including IDE, NES Emulator, FamiTracker-Qt, and FamiPlayer

set -e  # Exit immediately if a command exits with a non-zero status

# Check for prerequisites
if [ -f "/etc/debian_version" ]; then
   echo "Checking for required packages..."
   if ! command -v clang++ &> /dev/null; then
       echo "clang++ not found. Please install Clang."
       echo "Run: sudo apt install clang"
       exit 1
   fi
   if ! command -v qmake &> /dev/null; then
       echo "qmake not found. Please install Qt5 development packages."
       echo "Run: sudo apt install qt5-qmake qtbase5-dev qtbase5-dev-tools libqt5opengl5-dev"
       exit 1
   fi
fi

# Set environment variables to use CLANG
export CC=clang
export CXX=clang++

echo "Using CLANG compiler:"
echo "CC = $CC"
echo "CXX = $CXX"

# Ensure dependencies are built
echo "Checking dependencies..."

# Save current directory to return to it later
ORIGINAL_DIR=$(pwd)

# Build RtMidi if not already built
if [ ! -f "../deps/rtmidi/librtmidi.a" ] && [ ! -f "../deps/rtmidi/debug/librtmidi.a" ] && [ ! -f "../deps/rtmidi/release/librtmidi.a" ]; then
    echo "Building RtMidi library with CLANG..."
    cd ../deps/rtmidi
    qmake rtmidi.pro -spec linux-clang
    make
    cd "$ORIGINAL_DIR"
fi

# Build QHexEdit2 if not already built
if [ ! -f "../deps/qhexedit2/src/libqhexedit.so" ] && [ ! -f "../deps/qhexedit2/lib/libqhexedit.so" ]; then
    echo "Building QHexEdit2 library with CLANG..."
    cd ../deps
    if [ ! -d "qhexedit2" ]; then
        echo "Cloning QHexEdit2..."
        git clone https://github.com/Simsys/qhexedit2.git
    fi
    cd qhexedit2/src
    qmake qhexedit.pro -spec linux-clang
    make
    mkdir -p ../lib
    cp libqhexedit.so* ../lib/
    cd "$ORIGINAL_DIR"
fi

# Build QScintilla2 if not already built
if [ ! -f "../deps/qscintilla2/src/libqscintilla2_qt5.so" ]; then
    echo "Building QScintilla2 library with CLANG..."
    cd ../deps/qscintilla2/src
    qmake qscintilla.pro -spec linux-clang CONFIG+=staticlib
    make
    cd "$ORIGINAL_DIR"
fi

# Copy source files to build directories if they don't exist
echo "Preparing build directories..."
if [ ! -f "ide/nesicide.pro" ]; then
    echo "Copying IDE source files to build directory..."
    mkdir -p ide
    cp -r ../apps/ide/* ./ide/ 2>/dev/null || echo "Using local IDE files if available"
    # Copy the project file specifically
    cp ../apps/ide/nesicide.pro ./ide/ 2>/dev/null || cp nesicide.pro ./ide/
fi

if [ ! -f "nes-emulator/nesicide-emulator.pro" ]; then
    echo "Copying NES Emulator source files to build directory..."
    mkdir -p nes-emulator
    cp -r ../apps/nes-emulator/* ./nes-emulator/ 2>/dev/null || echo "Using local emulator files if available"
    cp ../apps/nes-emulator/nesicide-emulator.pro ./nes-emulator/ 2>/dev/null || echo "Emulator project file not found locally"
fi

if [ ! -f "famitracker-qt/src/famitracker-qt.pro" ]; then
    echo "Copying FamiTracker-Qt source files to build directory..."
    mkdir -p famitracker-qt/src
    cp -r ../apps/famitracker-qt/src/* ./famitracker-qt/src/ 2>/dev/null || echo "Using local famitracker-qt files if available"
    cp ../apps/famitracker-qt/src/famitracker-qt.pro ./famitracker-qt/ 2>/dev/null || echo "FamiTracker-Qt project file not found locally"
fi

if [ ! -f "famiplayer/famiplayer.pro" ]; then
    echo "Copying FamiPlayer source files to build directory..."
    mkdir -p famiplayer
    cp -r ../apps/famiplayer/* ./famiplayer/ 2>/dev/null || echo "Using local famiplayer files if available"
    cp ../apps/famiplayer/famiplayer.pro ./famiplayer/ 2>/dev/null || echo "FamiPlayer project file not found locally"
fi

# Build all components with CLANG
echo "Building NESICIDE with CLANG..."
( cd ide && qmake nesicide.pro -spec linux-clang CONFIG+=debug && make QSCINTILLA_NAME=qscintilla2_qt5 QHEXEDIT_NAME=qhexedit )

echo "Building NES Emulator with CLANG..."
( cd nes-emulator && qmake nesicide-emulator.pro -spec linux-clang CONFIG+=debug && make )

echo "Building FamiTracker-Qt with CLANG..."
( cd famitracker-qt/src && qmake famitracker-qt.pro -spec linux-clang CONFIG+=debug && make )

echo "Building FamiPlayer with CLANG..."
( cd famiplayer && qmake famiplayer.pro -spec linux-clang CONFIG+=debug && make )

echo ""
echo "SUCCESS: All components built with CLANG!"
echo "Built executables:"
echo "  - NESICIDE IDE: $(pwd)/ide/debug/nesicide"
echo "  - NES Emulator: $(pwd)/nes-emulator/debug/nesicide-emulator"
echo "  - FamiTracker-Qt: $(pwd)/famitracker-qt/src/debug/famitracker-qt"
echo "  - FamiPlayer: $(pwd)/famiplayer/debug/famiplayer"
echo ""

exit 0