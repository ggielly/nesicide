#!/bin/bash

# Script pour lier NESICIDE IDE

set -e  # Arrêter en cas d'erreur

echo "Liaison de l'exécutable NESICIDE..."
cd /home/etc/src/nesicide/build/ide

# D'abord, assurons-nous que tous les fichiers objets nécessaires sont compilés
echo "Vérification des fichiers objets..."
OBJECTS=$(find debug -name "*.o")
if [ -z "$OBJECTS" ]; then
    echo "Aucun fichier objet trouvé. Veuillez d'abord compiler les fichiers objets."
    exit 1
fi

echo "Trouvé $(echo "$OBJECTS" | wc -l) fichiers objets"

# Essayons de lier avec un timeout
echo "Liaison de l'exécutable..."
timeout 120 make -j1 debug/nesicide

if [ $? -eq 0 ]; then
    echo "Liaison réussie!"
    ls -lh debug/nesicide
else
    echo "La liaison a échoué ou a dépassé le timeout"
    echo "Vous pouvez essayer de lier manuellement avec :"
    echo "g++ -o debug/nesicide $(find debug -name "*.o") -L../../libs/nes/debug -lnes-emulator -L../../libs/c64/debug -lc64-emulator -L../../libs/famitracker/debug -lfamitracker -lSDL -llua5.1 -L../../deps/qscintilla2/src -lqscintilla2_qt5 -L../../deps/qhexedit2/lib -lqhexeditd -L../../deps/rtmidi/debug -lrtmidi -lQt5OpenGL -lQt5Widgets -lQt5Gui -lQt5Network -lQt5Xml -lQt5Core -lGL -lpthread"
fi
