#!/bin/bash

echo "Building nesicide IDE with workaround for famitracker library..."
echo "==============================================================="

# Create build directory for IDE
mkdir -p build/ide

# Copy source files
cp -r ../apps/ide/* build/ide/
cp ../apps/ide/nesicide.pro build/ide/

# Create a modified version of the project file without famitracker dependencies
cd build/ide

# Backup original
cp nesicide.pro nesicide.pro.original

# Create a version without famitracker references
awk '
BEGIN { in_block = 0 }
/^FAMITRACKER_CXXFLAGS/ { in_block = 1; next }
/^FAMITRACKER_LIBS/ { in_block = 1; next }
/^FAMITRACKER_LFLAGS/ { in_block = 1; next }
/^.*libfamitracker.*dylib/ { in_block = 1; next }
/^.*libfamitracker.*\.so/ { in_block = 1; next }
/^}/ && in_block { in_block = 0; next }
in_block { next }
{ print }
' nesicide.pro.original > nesicide.pro

# Build the IDE
echo "Running qmake..."
qmake nesicide.pro -spec linux-g++ CONFIG+=debug

if [ $? -eq 0 ]; then
    echo "Building nesicide IDE..."
    make
    
    if [ $? -eq 0 ]; then
        echo ""
        echo "SUCCESS: nesicide IDE built successfully!"
        echo "Location: $(pwd)/debug/nesicide"
        echo ""
        echo "To run: ./debug/nesicide"
        echo ""
        echo "Note: FamiTracker functionality will be handled separately by FamiTracker-Qt"
    else
        echo "ERROR: Failed to build nesicide IDE"
        exit 1
    fi
else
    echo "ERROR: Failed to run qmake"
    exit 1
fi