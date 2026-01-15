#!/bin/bash

# Simple build script for nesicide IDE using CLANG
# This script builds only the main IDE application with CLANG

set -e  # Exit immediately if a command exits with a non-zero status

BUILD_TYPE="debug"

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
      echo "Build nesicide IDE with CLANG"
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

echo "Building nesicide IDE with CLANG ($BUILD_TYPE)"

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

# Build RtMidi if not already built
if [ ! -f "../deps/rtmidi/librtmidi.a" ] && [ ! -f "../deps/rtmidi/debug/librtmidi.a" ] && [ ! -f "../deps/rtmidi/release/librtmidi.a" ]; then
    echo "Building RtMidi library with CLANG..."
    cd ../deps/rtmidi
    qmake rtmidi.pro -spec linux-clang CONFIG+=$BUILD_TYPE
    make
    cd - > /dev/null
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
    qmake qhexedit.pro -spec linux-clang CONFIG+=$BUILD_TYPE
    make
    mkdir -p ../lib
    cp libqhexedit.so* ../lib/
    cd - > /dev/null
fi

# Build QScintilla2 if not already built
if [ ! -f "../deps/qscintilla2/src/libqscintilla2_qt5.so" ]; then
    echo "Building QScintilla2 library with CLANG..."
    cd ../deps/qscintilla2/src
    qmake qscintilla.pro -spec linux-clang CONFIG+=$BUILD_TYPE CONFIG+=staticlib
    make
    cd - > /dev/null
fi

# Build the IDE
echo "Building nesicide IDE with CLANG ($BUILD_TYPE)..."
qmake nesicide.pro -spec linux-clang CONFIG+=$BUILD_TYPE
make QSCINTILLA_NAME=qscintilla2_qt5 QHEXEDIT_NAME=qhexedit

echo ""
echo "SUCCESS: nesicide IDE built with CLANG ($BUILD_TYPE)!"
echo "Executable location: $(pwd)/$BUILD_TYPE/nesicide"
echo ""
echo "To run: ./debug/nesicide"  # Assuming debug build
echo ""

exit 0