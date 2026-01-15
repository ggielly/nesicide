#!/bin/bash

# Advanced build script for nesicide project using CLANG instead of GCC
# This script builds the entire project including IDE, NES Emulator, FamiTracker-Qt, and FamiPlayer
# Supports both debug and release builds

set -e  # Exit immediately if a command exits with a non-zero status

# Default build configuration
BUILD_TYPE="debug"
SPEC="linux-clang"

# Parse command line arguments
while [[ $# -gt 0 ]]; do
  case $1 in
    -r|--release)
      BUILD_TYPE="release"
      shift
      ;;
    -d|--debug)
      BUILD_TYPE="debug"
      shift
      ;;
    -h|--help)
      echo "Usage: $0 [OPTIONS]"
      echo "Build nesicide project with CLANG"
      echo ""
      echo "Options:"
      echo "  -d, --debug     Build debug version (default)"
      echo "  -r, --release   Build release version"
      echo "  -h, --help      Show this help message"
      echo ""
      exit 0
      ;;
    *)
      echo "Unknown option: $1"
      echo "Use -h or --help for usage information"
      exit 1
      ;;
  esac
done

echo "Build configuration: $BUILD_TYPE"

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
export QMAKE_CC=clang
export QMAKE_CXX=clang++

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
    qmake rtmidi.pro -spec $SPEC CONFIG+=$BUILD_TYPE
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
    qmake qhexedit.pro -spec $SPEC CONFIG+=$BUILD_TYPE
    make
    mkdir -p ../lib
    cp libqhexedit.so* ../lib/
    cd "$ORIGINAL_DIR"
fi

# Build QScintilla2 if not already built
if [ ! -f "../deps/qscintilla2/src/libqscintilla2_qt5.so" ]; then
    echo "Building QScintilla2 library with CLANG..."
    cd ../deps/qscintilla2/src
    qmake qscintilla.pro -spec $SPEC CONFIG+=$BUILD_TYPE CONFIG+=staticlib
    make
    cd "$ORIGINAL_DIR"
fi

# Prepare build directories
echo "Preparing build directories..."

# Create directories if they don't exist
mkdir -p ide nes-emulator famitracker-qt/src famiplayer

# Copy source files to build directories if they don't exist
if [ ! -f "ide/nesicide.pro" ]; then
    echo "Copying IDE source files to build directory..."
    if [ -d "../apps/ide" ]; then
        cp -r ../apps/ide/* ./ide/
        cp ../apps/ide/nesicide.pro ./ide/ 2>/dev/null || cp nesicide.pro ./ide/
    else
        echo "Warning: ../apps/ide directory not found, using local files"
        cp nesicide.pro ./ide/
    fi
fi

if [ ! -f "nes-emulator/nesicide-emulator.pro" ]; then
    echo "Copying NES Emulator source files to build directory..."
    if [ -d "../apps/nes-emulator" ]; then
        cp -r ../apps/nes-emulator/* ./nes-emulator/
        cp ../apps/nes-emulator/nesicide-emulator.pro ./nes-emulator/
    else
        echo "Warning: ../apps/nes-emulator directory not found, checking for local file"
        if [ -f "nesicide-emulator.pro" ]; then
            cp nesicide-emulator.pro ./nes-emulator/
        else
            echo "Error: Cannot find nesicide-emulator.pro file"
            exit 1
        fi
    fi
fi

if [ ! -f "famitracker-qt/src/famitracker-qt.pro" ]; then
    echo "Copying FamiTracker-Qt source files to build directory..."
    if [ -d "../apps/famitracker-qt/src" ]; then
        cp -r ../apps/famitracker-qt/src/* ./famitracker-qt/src/
        cp ../apps/famitracker-qt/src/famitracker-qt.pro ./famitracker-qt/
    else
        echo "Warning: ../apps/famitracker-qt/src directory not found, checking for local file"
        if [ -f "famitracker-qt.pro" ]; then
            cp famitracker-qt.pro ./famitracker-qt/
        else
            echo "Warning: Cannot find famitracker-qt.pro file, continuing without FamiTracker-Qt"
        fi
    fi
fi

if [ ! -f "famiplayer/famiplayer.pro" ]; then
    echo "Copying FamiPlayer source files to build directory..."
    if [ -d "../apps/famiplayer" ]; then
        cp -r ../apps/famiplayer/* ./famiplayer/
        cp ../apps/famiplayer/famiplayer.pro ./famiplayer/
    else
        echo "Warning: ../apps/famiplayer directory not found, checking for local file"
        if [ -f "famiplayer.pro" ]; then
            cp famiplayer.pro ./famiplayer/
        else
            echo "Warning: Cannot find famiplayer.pro file, continuing without FamiPlayer"
        fi
    fi
fi

# Build all components with CLANG
echo "Building NESICIDE with CLANG ($BUILD_TYPE)..."
if [ -f "ide/nesicide.pro" ]; then
    ( cd ide && qmake nesicide.pro -spec $SPEC CONFIG+=$BUILD_TYPE && make QSCINTILLA_NAME=qscintilla2_qt5 QHEXEDIT_NAME=qhexedit )
else
    echo "Warning: IDE project file not found, skipping IDE build"
fi

echo "Building NES Emulator with CLANG ($BUILD_TYPE)..."
if [ -f "nes-emulator/nesicide-emulator.pro" ]; then
    ( cd nes-emulator && qmake nesicide-emulator.pro -spec $SPEC CONFIG+=$BUILD_TYPE && make )
else
    echo "Warning: NES Emulator project file not found, skipping emulator build"
fi

echo "Building FamiTracker-Qt with CLANG ($BUILD_TYPE)..."
if [ -f "famitracker-qt/src/famitracker-qt.pro" ]; then
    ( cd famitracker-qt/src && qmake famitracker-qt.pro -spec $SPEC CONFIG+=$BUILD_TYPE && make )
else
    echo "Warning: FamiTracker-Qt project file not found, skipping FamiTracker-Qt build"
fi

echo "Building FamiPlayer with CLANG ($BUILD_TYPE)..."
if [ -f "famiplayer/famiplayer.pro" ]; then
    ( cd famiplayer && qmake famiplayer.pro -spec $SPEC CONFIG+=$BUILD_TYPE && make )
else
    echo "Warning: FamiPlayer project file not found, skipping FamiPlayer build"
fi

echo ""
echo "SUCCESS: All available components built with CLANG ($BUILD_TYPE)!"
echo "Built executables:"
if [ -f "ide/$BUILD_TYPE/nesicide" ]; then
    echo "  - NESICIDE IDE: $(pwd)/ide/$BUILD_TYPE/nesicide"
fi
if [ -f "nes-emulator/$BUILD_TYPE/nesicide-emulator" ]; then
    echo "  - NES Emulator: $(pwd)/nes-emulator/$BUILD_TYPE/nesicide-emulator"
fi
if [ -f "famitracker-qt/src/$BUILD_TYPE/famitracker-qt" ]; then
    echo "  - FamiTracker-Qt: $(pwd)/famitracker-qt/src/$BUILD_TYPE/famitracker-qt"
fi
if [ -f "famiplayer/$BUILD_TYPE/famiplayer" ]; then
    echo "  - FamiPlayer: $(pwd)/famiplayer/$BUILD_TYPE/famiplayer"
fi
echo ""

exit 0