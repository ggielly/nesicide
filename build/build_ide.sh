#!/bin/bash

# Script pour compiler l'IDE de nesicide avec tous les dépendances correctes

echo "Setting up environment for nesicide IDE compilation..."
echo "====================================================="

# Définir les variables d'environnement pour les chemins
export TOP="$(pwd)/.."
export DEPENDENCYROOTPATH="../deps"
export DEPENDENCYPATH="../deps"

echo "TOP is set to: $TOP"
echo "DEPENDENCYROOTPATH is set to: $DEPENDENCYROOTPATH"

# Vérifier que les dépendances existent
if [ ! -d "../deps/rtmidi" ]; then
    echo "Creating symlink for rtmidi dependency..."
    mkdir -p ../deps
    ln -sf ../deps/rtmidi-source ../deps/rtmidi
fi

# Vérifier que les bibliothèques existent
if [ ! -d "../libs/nes" ]; then
    echo "Creating symlink for nes library..."
    mkdir -p ../libs
    ln -sf ../libs/nes ../libs/nes
fi

if [ ! -d "../libs/c64" ]; then
    echo "Creating symlink for c64 library..."
    ln -sf ../libs/c64 ../libs/c64
fi

if [ ! -d "../libs/famitracker" ]; then
    echo "Creating symlink for famitracker library..."
    ln -sf ../build/famitracker-qt/src ../libs/famitracker
fi

# Copier les fichiers communs au bon endroit
if [ ! -d "../common" ]; then
    echo "Creating common directory..."
    mkdir -p ../common
    cp -r ../common/* ../common/ 2>/dev/null || echo "Common directory prepared"
fi

# Remplacer les dépendances famitracker problématiques dans le fichier projet
echo "Updating project file to use working famitracker library..."
sed -i 's|$$TOP/libs/famitracker|../build/famitracker-qt/src|g' nesicide.pro

# Lancer qmake avec les paramètres corrects
echo "Running qmake..."
qmake nesicide.pro -spec linux-g++ CONFIG+=debug

if [ $? -eq 0 ]; then
    echo "qmake successful, now building IDE..."
    make
    if [ $? -eq 0 ]; then
        echo ""
        echo "SUCCESS: nesicide IDE compiled successfully!"
        echo "Executable location: $(pwd)/debug/nesicide"
        echo ""
        echo "To run: ./debug/nesicide"
    else
        echo "ERROR: Failed to build nesicide IDE"
        exit 1
    fi
else
    echo "ERROR: qmake failed"
    exit 1
fi