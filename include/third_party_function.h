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
 * @file third_party_function.h
 * @brief Prototypes of functions used for third_party_function's algorithm.
 */

/**
 * @author STEIMETZ Tangui <steimetz.tangui@ecole.ensicaen.fr>
 * @author PICQUE Kylian <picque.kylian@ecole.ensicaen.fr>
 * @version 3.0.0
 * @date 28 decembre 2021
 */ 

#ifndef __THIRD_PARTY_FUNCTION_HH__
#define __THIRD_PARTY_FUNCTION_HH__

#include <stdlib.h>
#include <stdio.h>

#include "image.h"
#include "table.h"
#include "kdtree.h"

/**
* @brief initializes and charge an image.
*
* @param file_name the picture's name.
*
* @return image variable from a picture.
*/
image init_image ( char* file_name );

/**
 * @brief makes a copy of an original image. This copy is initializes at zero.
 * 
 * @param original_img reference image
 *
 * @return image variable
 */
image copy_image_zero ( image original_img );

/**
 * @brief displays a color table;
 * 
 * @param tab the table of color. 
 * @param size the size of the table.
 * 
 */
void displayTab ( unsigned char* tab, int size );

/**
 * @brief displays a color table on a specific axis(rgb).
 * 
 * @param tab the table of color. 
 * @param size the table's size.
 * @param ref_axis the reference axis.
 * 
 */
void displayTabOnAxis ( unsigned char* tab, int size, axis ref_axis );

#endif /* __THIRD_PARTY_FUNCTION_HH__ */