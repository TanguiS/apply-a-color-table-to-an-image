#!/bin/bash
#
# ENSICAEN
# 6 Boulevard Maréchal Juin
# F −14050 Caen Cedex
#
# This fileis owned by ENSICAEN students.
# It cannot be reproduced, used or modified without
# permission of its authors.
#

#
# This script performs the gnuplot's seuil.
# Steimetz Tangui <tangui.steimetz@ecole.ensicaen.fr>
# Picque Kylian <kylian.picque@ecole.ensicaen.fr>
# Version 1.0.0 / 03/01/2022
#

#Liste des entrées à fournir au script
IMG_NAME=$1 #Nom de l'image
TABLE_NAME=$2 #Nom de la table de couleurs
PATH_SCRIPT=$3 #Direction du dossier des scripts
PATH_GRAPH=$4 #Direction du dossier des graphiques
SEUIL=$5 #Données de la méthode kdtree avec variation de seuil

SCRIPT="$PATH_SCRIPT/scriptgraphseuil.conf" #Fichier de configuration du graphique

#Edition du fichier de configuration
echo "$PATH_NAME $PATH_GRAPH $SCRIPT"
echo "set title 'Comparaison des temps de $IMG_NAME de $TABLE_NAME avec variation de seuil'" > $SCRIPT
echo "set xlabel 'seuil'" >> $SCRIPT
echo "set ylabel 'temps(s)'" >> $SCRIPT
echo "set autoscale" >> $SCRIPT
echo "set key left top" >> $SCRIPT
echo "set term png size 1080,720" >> $SCRIPT
echo "set output '$PATH_GRAPH/$IMG_NAME-$TABLE_NAME-seuil.png'" >> $SCRIPT
echo "plot \
'$SEUIL' \
using 3:1 with linespoints title 'variation seuil' lt 7 lc 7 ps 1" >> $SCRIPT

#Création du graphique
gnuplot > load "$SCRIPT"








