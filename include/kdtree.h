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
 * @file kdtree.h
 * @brief Prototypes of functions used for kdtree's algorithm.
 */

/**
 * @author STEIMETZ Tangui <steimetz.tangui@ecole.ensicaen.fr>
 * @author PICQUE Kylian <picque.kylian@ecole.ensicaen.fr>
 * @version 3.0.0
 * @date 23 decembre 2021
 */ 

#ifndef __KDTREE_HH__
#define __KDTREE_HH__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "table.h"
#include "third_party_function.h"
#include "image.h"

#define DIM 3 /*!< Pixel size */

typedef struct _kdtree *kdtree; /*!< Kdtree type definition */

typedef enum {left, right} status_son; /*!< state of a kdtree's son in 
    comparaison to his kdtree's parent */

/**
 * @brief Creates a kdtree.
 *
 * @param reference_table the color table of reference. 
 * @param cardinal_max the maximum size of the table.
 *
 * @return The kdtree properly defined.
 */
kdtree create_kdtree ( color_table reference_table, int cardinal_max );

/**
 * @brief Destroy a kdtree.
 *
 * @param kdtree_to_destroy the kdtree to destroy. 
 *
 * @return The boolean check.
 */
boolean destroy_kdtree ( kdtree kdtree_to_destroy );

/**
 * @brief Initializes the kdtree.
 *
 * @param kdtree_to_init the kdtree to initialize. 
 *
 * @return The kdtree properly initialized.
 */
kdtree init_kdtree ( kdtree kdtree_to_init );

/**
 * @brief Returns the axis with the largest projection.
 *
 * @param reference_kdtree the kdtree of reference. 
 *
 * @return The reference axis of a kdtree.
 */
axis get_kdtree_sectional_axis ( kdtree reference_kdtree );

/**
 * @brief Returns the position of the cutting plane orthogonal to the chosen axis.
 *
 * @param reference_kdtree the kdtree of reference. 
 *
 * @return The position of the cutting plan orthogonal.
 */
float get_kdtree_cutting_plan ( kdtree reference_kdtree );

/**
 * @brief Gets the color table of a kdtree.
 *
 * @param reference_kdtree the kdtree of reference. 
 *
 * @return The color table of a kdtree.
 */
color_table get_kdtree_table_color ( kdtree reference_kdtree );

/**
 * @brief Gets the left son'skdtree of a parent kdtree.
 *
 * @param parent_kdtree the kdtree of reference. 
 *
 * @return The left son of a kdtree.
 */
kdtree get_kdtree_left_son ( kdtree parent_kdtree );

/**
 * @brief Gets the right son'skdtree of a parent kdtree.
 *
 * @param parent_kdtree the kdtree of reference. 
 *
 * @return The right son of a kdtree.
 */
kdtree get_kdtree_right_son ( kdtree parent_kdtree );

/**
 * @brief Sets the sectionnal axis to a kdtree.
 *
 * @param reference_kdtree the kdtree of reference. 
 * @param set_sectionnal the choosen sectionnal axis.
 *
 * @return The kdtree's sectionnal axis setted.
 */
void set_kdtree_sectional_plan ( kdtree reference_kdtree, axis set_sectional );

/**
 * @brief Sets the cutting plan orthogonal to a kdtree.
 *
 * @param reference_kdtree the kdtree of reference. 
 * @param set_cutting the choosen orthogonal cutting plan axis.
 *
 * @return The kdtree's orthogonal cutting plan setted.
 */
void set_kdtree_cutting_plan ( kdtree reference_kdtree, float set_cutting );

/**
 * @brief Sets the color table to a kdtree.
 *
 * @param reference_kdtree the kdtree of reference. 
 * @param reference_table the color table of reference.
 *
 * @return The kdtree's color table setted.
 */
void set_kdtree_color_table ( kdtree reference_kdtree, 
    color_table reference_table );

/**
 * @brief Sets the left son to a parent kdtree.
 *
 * @param parent_kdtree the parent kdtree. 
 * @param left_son_kdtree the left son kdtree of the parent kdtree.
 *
 * @return The kdtree's left son setted.
 */
void set_kdtree_left_son ( kdtree parent_kdtree, kdtree left_son_kdtree );

/**
 * @brief Sets the right son to a parent kdtree.
 *
 * @param parent_kdtree the parent kdtree. 
 * @param right_son_kdtree the right son kdtree of the parent kdtree.
 *
 * @return The kdtree's right son setted.
 */
void set_kdtree_right_son ( kdtree parent_kdtree, kdtree right_son_kdtree );

/**
 * @brief Separates the kdtree's color table into two differents color table.
 *
 * @param reference_kdtree the kdtree of reference. 
 * @param inferior_table the inferior color table according to the cutting 
 * orthogonal plan.
 * @param superior_table the superior color table according to the cutting
 * orthogonal plan.
 *
 * @return The splited color table.
 */
void split_color_table ( kdtree reference_kdtree, color_table* inferior_table, 
    color_table* superior_table );

/**
 * @brief Founds the nearest color of a reference color.
 *
 * @param perant_kdtree the kdtree of reference. 
 * @param reference_color the color of reference.
 * @param buf the nearest color of the reference's color
 *
 * @return The buf filled with the nearest color of reference_color.
 */
void kdtree_get_nearest_color ( kdtree reference_kdtree, 
    color* reference_color, color* buf);

#endif /* __KDTREE_HH__ */