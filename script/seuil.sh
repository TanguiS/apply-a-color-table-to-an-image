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
# This script performs the seuil.
# Steimetz Tangui <tangui.steimetz@ecole.ensicaen.fr>
# Picque Kylian <kylian.picque@ecole.ensicaen.fr>
# Version 1.1.0 / 03/01/2022
#

PATH_IMAGE="./ressource/IMAGES/" #Direction du répertoire d'images
PATH_TABLE="./ressource/IMAGES/TABLES/" #Direction du répertoire de tables
PATH_SCRIPT="./script" #Direction du répertoire de scipts
PATH_GRAPH="$PATH_SCRIPT/graph" #Direction du répertoire des graphiques
PATH_DATA="$PATH_SCRIPT/data" #Direction du répertoire des données

make kdtree
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

echo -n "Entrer le nom et son extension de la table de couleurs (q, pour quitter) : "
read nom_table

TABLE="$PATH_TABLE$nom_table" #Direction du répertoire de la table de couleurs

#Vérifie que l'entrée est correcte 
while [ $nom_table != "q" -a ! -e $TABLE ]
    do
    echo -n "Ce fichier n'existe pas. Entrer le nom et son extension de la table de couleurs (q, pour quitter) : "
    read nom_table
    TABLE="$PATH_TABLE$nom_table"
    echo "$TABLE"
    done

if [ $nom_table = "q" ]
    then
    exit
fi

#Direction des données produits par la méthode kdtree
KDTREE="$PATH_DATA/seuil_kdtree_$nom_img_$nom_table.dat"

touch $KDTREE
echo "# temps(s) largueur_table(pixel) seuil" > $KDTREE

#Execution de la table de couleurs à l'image à traiter en variant le seuil
MIN=1
MAX=999
PAS=7
let counter=$MIN
while [ $MAX -gt $counter ]
do
    echo "exec : ./bin/kdtree_method $IMAGE $TABLE $counter"
    ./bin/kdtree_method $IMAGE $TABLE $counter >> $KDTREE
    let counter="$counter + $PAS"
done

#Appel au script de construction du graphique 
$PATH_SCRIPT/gnuplot_seuil.sh $nom_img $nom_table $PATH_SCRIPT $PATH_GRAPH $KDTREE