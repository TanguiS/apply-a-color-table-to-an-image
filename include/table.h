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
 * @file table.h
 * @brief Prototypes of functions used for table's algorithm.
 */

/**
 * @author STEIMETZ Tangui <steimetz.tangui@ecole.ensicaen.fr>
 * @author PICQUE Kylian <picque.kylian@ecole.ensicaen.fr>
 * @version 3.0.0
 * @date 23 decembre 2021
 */ /*!<  */

#ifndef __TABLE_HH__
#define __TABLE_HH__

#include <stdlib.h>
#include <stdio.h>

#include "image.h"

#define DIM 3 /*!< Pixel size */ 

typedef enum {red, green, blue} axis; /*!< Definition of an image axis */

typedef unsigned char color; /*!< Color type definition */

typedef enum {false, true} boolean; /*!< Boolean type definition */

typedef struct _color_table *color_table; /*!< Color table type definition */

struct _save_pixel {
    color pixel[DIM];
    int lenth;
};
typedef struct _save_pixel save_pixel; /*!< save pixel type */ 

/**
 * @brief Creates a color table.
 *
 * @param img_1D the 1 size structure image. 
 *
 * @return The color table properly defined.
 */
color_table		create_color_table ( image img_1D );

/**
 * @brief Initializes a color table.
 *
 * @param table_to_init the color table uninitialized. 
 *
 * @return The color table properly initialized.
 */
color_table     init_color_table ( color_table table_to_init );

/**
 * @brief Returns the table of colors.
 *
 * @param reference_table the color table of reference. 
 * @param offset the shift in the beginning of the table.
 *
 * @return The table of colors shifted of offset.
 */
color*		   get_color_table_tab ( color_table reference_table, int offset );

/**
 * @brief Sets the table's colors.
 *
 * @param reference_table the color table of reference. 
 * @param set_offset the shift in the beginning of the table.
 *
 * @return The color table with the table of colors shifted of offset.
 */
void 	        set_color_table_tab ( color_table reference_table, 
                    color* reference_tab, int set_offset );

/**
 * @brief Returns the table's owner.
 *
 * @param reference_table the color table of reference. 
 *
 * @return The color table's owner.
 */
boolean 		get_color_table_owner ( color_table reference_table );

/**
 * @brief Sets the table's colors.
 *
 * @param reference_table the color table of reference. 
 * @param set_owner the new owner's value.
 *
 * @return The color table with the new owner.
 */
void 			set_color_table_owner ( color_table reference_table, 
                    boolean set_owner );

/**
 * @brief Returns the table's width.
 *
 * @param reference_table the color table of reference. 
 *
 * @return The color table's width.
 */
int 			get_color_table_width ( color_table reference_table );

/**
 * @brief Sets the table's width.
 *
 * @param reference_table the color table of reference. 
 * @param set_width the new width's table.
 *
 * @return The color table with the new width.
 */
void 			set_color_table_width ( color_table reference_table, 
                    int set_width );

/**
 * @brief Destroys the color table.
 *
 * @param table_to_destroy the color table to destroy. 
 *
 * @return The boolean check.
 */
boolean 		destroy_color_table ( color_table table_to_destroy );

/**
 * @brief Duplicate a color table.
 *
 * @param reference_table the color table of reference. 
 * @param offset the shift in the beginning of the table.
 * @param width_sub_table the duplicated color table's width.
 *
 * @return The duplicate color table shifted of an offset, with a width.
 */
color_table		color_table_duplicate ( color_table reference_table, 
                    int offset, int width_sub_table );

/**
 * @brief Gets a pixel's rate.
 *
 * @param reference_table the color table of reference. 
 * @param index the index of the wanted pixel.
 * @param buf the buffer to get the pixel's rate.
 *
 * @return The buffer with a pixel's rate shifted of an index.
 */
void 			color_table_get_color ( color_table reference_table, 
                    int index, color* buf );

/*
 * Fonctions pour comparer l'intensité de couleurs Red, Grenn & Blue d'un pixel
 */

/**
 * @brief The differences of two constants.
 *
 * @param first the first constant. 
 * @param second the second constant.
 *
 * @return The differences in red rate of two pixels.
 */
int				redComparator (const void* first, const void *second);

/**
 * @brief The differences of two constants.
 *
 * @param first the first constant. 
 * @param second the second constant.
 *
 * @return The differences in green rate of two pixels.
 */
int           	greenComparator (const void* first, const void *second);

/**
 * @brief The differences of two constants.
 *
 * @param first the first constant. 
 * @param second the second constant.
 *
 * @return The differences in blue rate of two pixels.
 */
int           	blueComparator (const void* first, const void *second);

/**
 * @brief Sorts a color of a color table.
 *
 * @param reference_table the color table of reference. 
 * @param rgb_switch the axis that will be sorted.
 *
 * @return The sorted color table according to the choosen axis.
 */
void			color_table_sort(color_table reference_table, axis rgb_switch);

/**
 * @brief Calculates the lenth between two arrays.
 * 
 * @param pix1 the first pixel.
 * @param pix2 the second pixel.
 * 
 * @return int, the distance between two pixel.
 */
int lenth_pixel ( color* pix1, color* pix2 );

/**
 * @brief Gets the closest pixel to the reference pixel, for an iterative algo.
 * 
 * @param reference_table the color table of reference.
 * @param reference_pixel the pixel's color of reference.
 * @param proxy_pixel the closest pixel to the pixel of reference.
 * 
 * @return the nearest pixel in a table of color of a reference one.
 */
void get_color_table_it_proxy_pixel ( color_table reference_table, 
    color* reference_pixel, save_pixel* proxy_pixel );

/**
 * @brief Gets the closest pixel to the reference pixel, for an recurrent algo.
 * 
 * @param reference_table the color table of reference.
 * @param reference_pixel the pixel's color of reference.
 * @param proxy_pixel the closest pixel to the pixel of reference.
 * 
 * @return the nearest pixel in a table of color of a reference one.
 */
void get_color_table_rec_proxy_pixel ( color_table reference_table,
    color* reference_pixel, save_pixel* buf );
    
#endif /* __TABLE_HH__ */