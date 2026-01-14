#!/bin/bash

echo "Building nesicide IDE without problematic famitracker dependency..."
echo "=================================================================="

# Create build directory for IDE
mkdir -p build/ide

# Copy IDE source files
cp -r ../apps/ide/* ./build/ide/
cp ../apps/ide/nesicide.pro ./build/ide/

# Modify the project file to remove problematic famitracker dependency
sed -i 's/FAMITRACKER_CXXFLAGS/#FAMITRACKER_CXXFLAGS/g' build/ide/nesicide.pro
sed -i 's/FAMITRACKER_LIBS/#FAMITRACKER_LIBS/g' build/ide/nesicide.pro
sed -i 's/-lfamitracker/#-lfamitracker/g' build/ide/nesicide.pro
sed -i 's/FAMITRACKER_LFLAGS/#FAMITRACKER_LFLAGS/g' build/ide/nesicide.pro

# Also remove the post-link commands that copy famitracker library
sed -i '/libfamitracker/d' build/ide/nesicide.pro

echo "Building IDE with modified project file..."
cd build/ide

# Build with qmake
qmake nesicide.pro -spec linux-g++ "QMAKE_CFLAGS+=-m64" "QMAKE_CXXFLAGS+=-m64" "QMAKE_LFLAGS+=-m64" CONFIG+=debug
make

if [ $? -eq 0 ]; then
    echo ""
    echo "SUCCESS: nesicide IDE built successfully without famitracker dependency!"
    echo "Executable location: $(pwd)/debug/nesicide"
    echo ""
    echo "To run: ./debug/nesicide"
    echo ""
    echo "Note: FamiTracker functionality will be handled by the standalone FamiTracker-Qt application:"
    echo "  - FamiTracker-Qt: ../build/famitracker-qt/src/famitracker"
else
    echo "ERROR: Failed to build nesicide IDE"
    exit 1
fi