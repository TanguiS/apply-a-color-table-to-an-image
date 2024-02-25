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
# This script performs the reset.
# Steimetz Tangui <tangui.steimetz@ecole.ensicaen.fr>
# Picque Kylian <kylian.picque@ecole.ensicaen.fr>
# Version 1.0.0 / 03/01/2022
#

#remove the datas
rm -f $1/*
#remove the graphs
rm -f $2/*
#remove the configuration's files
rm -f $3/*.conf
