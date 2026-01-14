#!/bin/bash

#
#if [ -f "/etc/debian_version" ]; then
#   sudo apt install build-essential libasound2-dev liblua5.1-dev libsdl1.2-dev \
#		libgl1-mesa-dev wine-dev libqt5opengl5-dev
#fi

# check for deps
#echo -n "Checking for dependencies package..."
#if [ ! -d "deps" ]; then
#if [ ! -d "../deps" ]; then
#   cd ..
#   echo "Fetching dependencies package..."
#   wget -q https://knob.phreneticappsllc.com/nesicide/nesicide-deps.tar.bz2
#   echo "Extracting dependencies package..."
#   tar -xjf nesicide-deps.tar.bz2 
#   rm -f nesicide-deps.tar.bz2
#   echo "Building dependencies..."
#
#  echo "Building dependencies..."
#   cd deps/rtmidi && qmake && make
#else
#   echo "found."
#fi

# add CONFIG+=debug to qmake to build debug.
echo Building NESICIDE...
( cd ide; qmake CONFIG+=debug; make )
echo Building FamiTracker...
( cd nes-emulator; qmake; make )
echo Building FamiPlayer...
( cd famiplayer; qmake; make )
echo Building NES Emulator...
( cd famitracker; qmake; make )

exit 0
