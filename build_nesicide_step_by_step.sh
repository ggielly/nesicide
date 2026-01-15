#!/bin/bash

# Script pour compiler NESICIDE IDE par étapes pour éviter les timeouts

set -e  # Arrêter en cas d'erreur

echo "Étape 1: Compilation des fichiers principaux..."
cd /home/etc/src/nesicide/build/ide
make -j6 debug/main.o debug/mainwindow.o debug/musiceditorform.o
echo "Étape 1 terminée avec succès"

echo "Étape 2: Compilation des fichiers de projet..."
make -j6 debug/cnesicideproject.o debug/cproject.o debug/cprojectbase.o debug/ccartridge.o
echo "Étape 2 terminée avec succès"

echo "Étape 3: Compilation des fichiers de l'interface utilisateur..."
make -j6 debug/aboutdialog.o debug/startupsplashdialog.o debug/environmentsettingsdialog.o
echo "Étape 3 terminée avec succès"

echo "Étape 4: Compilation des fichiers de l'émulateur NES..."
make -j6 debug/nesemulatorcontrol.o debug/nesemulatordockwidget.o debug/nesemulatorrenderer.o
echo "Étape 4 terminée avec succès"

echo "Étape 5: Compilation des fichiers du débogueur..."
make -j6 debug/cdebuggerbase.o debug/codebrowserdockwidget.o debug/breakpointdockwidget.o
echo "Étape 5 terminée avec succès"

echo "Étape 6: Compilation des fichiers restants..."
make -j6 debug/cbuildertextlogger.o debug/cdockwidgetregistry.o debug/filepropertiesdialog.o
echo "Étape 6 terminée avec succès"

echo "Toutes les étapes de compilation des fichiers objets sont terminées avec succès!"
echo "Vous pouvez maintenant essayer de lier l'exécutable avec: make -j1 debug/nesicide"
