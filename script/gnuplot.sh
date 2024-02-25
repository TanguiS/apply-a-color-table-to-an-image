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
# This script performs the gnuplot's graph.
# Steimetz Tangui <tangui.steimetz@ecole.ensicaen.fr>
# Picque Kylian <kylian.picque@ecole.ensicaen.fr>
# Version 1.2.1 / 03/01/2022
#

#Liste des entrées à fournir au script
IMG_NAME=$1 #Le nom de l'image
PATH_SCRIPT=$2 #Direction du dossier des scripts
PATH_GRAPH=$3 #Direction du dossier des graphiques
KDTREE=$4 #Données de la méthode kdtree
TRIVIAL=$5 #Données de la méthode trivial

SCRIPT="$PATH_SCRIPT/scriptgraph.conf" #Fichier de configuration du graphique

#Edition du fichier de configuration
echo "set title 'Comparaison des temps de $IMG_NAME'" > $SCRIPT
echo "set xlabel 'largueur table(pixel)'" >> $SCRIPT
echo "set ylabel 'temps(s)'" >> $SCRIPT
echo "set autoscale" >> $SCRIPT
echo "set key left top" >> $SCRIPT
echo "set term png size 1080,720" >> $SCRIPT
echo "set output '$PATH_GRAPH/$IMG_NAME.png'" >> $SCRIPT
echo "plot \
'$KDTREE' \
using 2:1 with points title 'kdtree method' pt 7 lc 7 ps 1.8, \
'$TRIVIAL' \
using 2:1 with points title 'trivial method' pt 7 lc 3 ps 1.6" >> $SCRIPT

#Création du graphique
gnuplot > load "$SCRIPT"