#!/bin/bash

echo "Building FamiTracker-Qt only (working version)..."
echo "==============================================="

# Create build directory structure
mkdir -p famitracker-qt/src

# Copy source files if they don't exist
if [ ! -f "famitracker-qt/src/famitracker-qt.pro" ]; then
    echo "Copying FamiTracker-Qt source files..."
    cp -r ../apps/famitracker-qt/src/* ./famitracker-qt/src/
    cp ../apps/famitracker-qt/src/famitracker-qt.pro ./famitracker-qt/
fi

echo "Building FamiTracker-Qt with 64-bit architecture..."
cd famitracker-qt/src

# Build with qmake
qmake famitracker-qt.pro -spec linux-g++ "QMAKE_CFLAGS+=-m64" "QMAKE_CXXFLAGS+=-m64" "QMAKE_LFLAGS+=-m64" CONFIG+=debug
make

if [ $? -eq 0 ]; then
    echo ""
    echo "SUCCESS: FamiTracker-Qt built successfully!"
    echo "Executable location: $(pwd)/famitracker"
    echo ""
    echo "To run: ./famitracker"
else
    echo "ERROR: Failed to build FamiTracker-Qt"
    exit 1
fi