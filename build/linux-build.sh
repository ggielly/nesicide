#!/bin/bash

# Find Qt
#. /opt/qt510/bin/qt510-env.sh

# add CONFIG+=debug to qmake to build debug.
echo Building NESICIDE...
( cd build/ide; /home/etc/code/qt/qt-5.12.6/5.12.6/gcc_64/bin/qmake; make )
echo Building FamiTracker...
( cd build/nes-emulator; /home/etc/code/qt/qt-5.12.6/5.12.6/gcc_64/bin/qmake; make )
echo Building FamiPlayer...
( cd build/famiplayer; /home/etc/code/qt/qt-5.12.6/5.12.6/gcc_64/bin/qmake; make )
echo Building NES Emulator...
( cd build/famitracker; /home/etc/code/qt/qt-5.12.6/5.12.6/gcc_64/bin/qmake; make )

exit 0
