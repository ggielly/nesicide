#!/bin/bash

# Script pour lier NESICIDE avec clang++ et lld

set -e  # Arrêter en cas d'erreur

echo "Liaison de NESICIDE avec clang++ et lld..."
cd /home/etc/src/nesicide/build/ide

echo "Configuration actuelle :"
echo "CXX = $(grep '^CXX' Makefile | cut -d'=' -f2 | tr -d ' ')"
echo "LINK = $(grep '^LINK' Makefile | cut -d'=' -f2 | tr -d ' ')"
echo "LFLAGS contient lld = $(grep 'fuse-ld=lld' Makefile | wc -l)"

echo "Nombre de fichiers objets : $(find debug -name "*.o" | wc -l)"
echo "Nombre de fichiers UI : $(find debug -name "ui_*" | wc -l)"

echo "Lancement de la liaison avec timeout 300s..."
timeout 300 make -j4 debug/nesicide

if [ $? -eq 0 ]; then
    echo "=== LIAISON RÉUSSIE ==="
    ls -lh debug/nesicide
    file debug/nesicide
    echo ""
    echo "L'exécutable a été créé avec succès!"
    echo "Vous pouvez l'exécuter avec : ./debug/nesicide"
else
    echo "La liaison a échoué ou a dépassé le timeout"
    if [ -f debug/nesicide ]; then
        echo "Fichier partiellement créé :"
        ls -lh debug/nesicide
        file debug/nesicide
    else
        echo "Aucun exécutable trouvé"
    fi
fi

echo "Fin du script"
