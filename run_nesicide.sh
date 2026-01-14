#!/bin/bash

# Script to run nesicide with proper library paths

SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"

# Set the library path to include all the required dependencies
export LD_LIBRARY_PATH=$SCRIPT_DIR/libs/nes/debug:$SCRIPT_DIR/libs/c64/debug:$SCRIPT_DIR/libs/famitracker/debug:$SCRIPT_DIR/deps/rtmidi:$SCRIPT_DIR/deps/qscintilla2/src:$SCRIPT_DIR/deps/qhexedit2/lib:$SCRIPT_DIR/deps/qhexedit2/src:$LD_LIBRARY_PATH

# Run the nesicide executable
exec $SCRIPT_DIR/build/ide/debian/usr/bin/nesicide "$@"