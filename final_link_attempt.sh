#!/bin/bash

# Script final pour lier NESICIDE IDE

set -e  # Arrêter en cas d'erreur

echo "Tentative finale de liaison de NESICIDE..."
cd /home/etc/src/nesicide/build/ide

echo "Étape 1: Vérification des fichiers objets..."
OBJECTS=$(find debug -name "*.o")
echo "Trouvé $(echo "$OBJECTS" | wc -l) fichiers objets"

echo "Étape 2: Vérification des fichiers UI..."
UI_FILES=$(find debug -name "ui_*")
echo "Trouvé $(echo "$UI_FILES" | wc -l) fichiers UI"

echo "Étape 3: Tentative de liaison avec make (timeout 180s)..."
timeout 180 make -j4 debug/nesicide

if [ $? -eq 0 ]; then
    echo "Liaison réussie!"
    ls -lh debug/nesicide
    file debug/nesicide
else
    echo "La liaison a échoué ou a dépassé le timeout"
    echo "Vérification si l'exécutable existe partiellement..."
    if [ -f debug/nesicide ]; then
        echo "Fichier trouvé, mais peut-être incomplet:"
        ls -lh debug/nesicide
        file debug/nesicide
    else
        echo "Aucun exécutable trouvé"
    fi
fi

echo "Fin du script de liaison"
