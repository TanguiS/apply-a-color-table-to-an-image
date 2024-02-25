/*
 * ENSICAEN
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex 
 * 
 * This file is owned by ENSICAEN students. No portion of this 
 * document may be reproduced, copied or revised without written 
 * permission of the authors.
 */

/**
 * @file color_switch.h
 * @brief Prototypes of functions used for color_switch's algorithm.
 */

/**
 * @author STEIMETZ Tangui <steimetz.tangui@ecole.ensicaen.fr>
 * @author PICQUE Kylian <picque.kylian@ecole.ensicaen.fr>
 * @version 1.8.0
 * @date 28 decembre 2021
 */ 

#ifndef __COLOR_SWITCH_HH__
#define __COLOR_SWITCH_HH__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "image.h"
#include "table.h"
#include "kdtree.h"
#include "third_party_function.h"

/**
 * @brief switches the image's color with the nearest one in the table
 * 
 * @param changed_image 
 * @param reference_table
 * 
 * @return a new image with the nearest color 
 */
image color_switch_trivial ( image changed_image, color_table reference_table );

/**
 * @brief switches the image's color with the nearest one in the table
 * 
 * @param changed_image 
 * @param reference_table
 * 
 * @return a new image with the nearest color 
 */
image color_switch_kdtree ( image changed_image, kdtree reference_kdtree );


/**
 * @brief give the name of the new image from the old
 * 
 * @param original_name 
 * @param table_name
 * @param new_name 
 * 
 * @return the new name of an image with the trivial method
 */
void name_new_image_table ( char* original_name, char* table_name, char* new_name);

/**
 * @brief give the name of the new image from the old
 * 
 * @param original_name 
 * @param table_name
 * @param new_name 
 * 
 * @return the new name of an image with the kdtree method
 */
void name_new_image_tree ( char* original_name, char* table_name, char* new_name);


#endif /* __COLOR_SWITCH_HH__ */
