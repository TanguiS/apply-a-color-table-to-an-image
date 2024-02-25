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
# This script performs the graph.
# Steimetz Tangui <tangui.steimetz@ecole.ensicaen.fr>
# Picque Kylian <kylian.picque@ecole.ensicaen.fr>
# Version 1.5.5 / 03/01/2022
#

PATH_IMAGE="./ressource/IMAGES/" #Direction du répertoire d'images
PATH_TABLE="./ressource/IMAGES/TABLES" #Direction du répertoire de tables
PATH_SCRIPT="./script" #Direction du répertoire de scipts
PATH_GRAPH="$PATH_SCRIPT/graph" #Direction du répertoire des graphiques
PATH_DATA="$PATH_SCRIPT/data" #Direction du répertoire des données

make inv
make clean
clear

echo -n "Entrer le nom et son extension de l'image à traiter (q, pour quitter) : "
read nom_img

IMAGE="$PATH_IMAGE$nom_img" #Direction du répertoire de l'image à traiter

#Vérifie que l'entrée est correcte 
while [ $nom_img != "q" -a ! -e $IMAGE ]
    do
    echo -n "Ce fichier n'existe pas. Entrer le nom et son extension de l'image à traiter (q, pour quitter) : "
    read nom_img
    IMAGE="$PATH_IMAGE$nom_img"
    done

if [ $nom_img = "q" ]
    then
    exit
fi

#Direction des données produits par la méthode kdtree
KDTREE="$PATH_DATA/temps_kdtree_$nom_img.dat"
#Direction des données produits par la méthode trivial
TRIVIAL="$PATH_DATA/temps_trivial_$nom_img.dat"

touch $KDTREE
touch $TRIVIAL
echo "# temps(s) largueur_table(pixel) seuil" > $KDTREE
echo "# temps(s) largueur_table(pixel)" > $TRIVIAL

#Execution de toutes les tables de couleurs à l'image à traiter
for table in $PATH_TABLE/*.ppm
do
    echo "exec : ./bin/kdtree_method $IMAGE $table"
    ./bin/kdtree_method $IMAGE $table 100 >> $KDTREE #seuil de 10% par default
    echo "exec : ./bin/trivial_method $IMAGE $table"
    ./bin/trivial_method $IMAGE $table >> $TRIVIAL #Redirige la sortie dans un fichier externe

done

#Appel au script de construction du graphique 
$PATH_SCRIPT/gnuplot.sh $nom_img $PATH_SCRIPT $PATH_GRAPH $KDTREE $TRIVIAL



