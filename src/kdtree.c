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
 * @file kdtree.c
 * @brief Functions of kdtree's algorithm.
 */

/**
 * @author STEIMETZ Tangui <steimetz.tangui@ecole.ensicaen.fr>
 * @author PICQUE Kylian <picque.kylian@ecole.ensicaen.fr>
 * @version 3.0.0
 * @date 23 decembre 2021
 */ /*!<  */
 
#include "kdtree.h"

struct _kdtree {
    /* kdtree's color table */
    color_table kdTable;
    /* kdtree's left son, which contains colors before the cutting plan */
    struct _kdtree* left_son;
    /* kdtree's left right, which contains colors after the cutting plan */
    struct _kdtree* right_son;
    /* kdtree's sectionnal axis, the longest projection */
    axis sectionalAxis;
    /* kdtree's cutting plan, the central line of the sectionnal axis */
    float cuttingPlan;
};

/*
 * The number of sons associated with the highest level kdtree
 */
static int height_kdtree = -1;

/**
 * @brief Founds the sectionnal axis of a kdtree.
 *
 * @param reference_kdtree the kdtree of reference. 
 *
 * @return The sectionnal axis of the kdtree of reference.
 */
static axis choice_reference_axis ( color_table reference_table );

/**
 * @brief Founds the central line of a kdtree's sorted table color of an axis.
 *
 * @param reference_kdtree the kdtree of reference. 
 * @param reference_axis the axis of reference.
 *
 * @return The central line of a kdtree.
 */
static float central_line_sorted ( color_table reference_table, axis reference_axis );

/**
 * @brief Founds the central line of a kdtree's unsorted table color of an axis.
 *
 * @param reference_kdtree the kdtree of reference. 
 * @param reference_axis the axis of reference.
 *
 * @return The central line of a kdtree.
 */
static float central_line_unsorted ( color_table reference_table, 
    axis reference_axis );

/**
 * @brief Assigns the kdtree's sons.
 *
 * @param parent_kdtree the kdtree of reference. 
 * @param cardinal_max the size max of a kdtree's color table.
 *
 * @return The assigned sons from the parent kdtree.
 */
static void assign_sons ( kdtree parent_kdtree, int cardinal_max );


kdtree create_kdtree ( color_table reference_table, int cardinal_max )
{
    kdtree kdtree_to_create = NULL; 
    axis reference_axis;
    float reference_cutting;
    int width; /* of the reference_table */

    assert ( reference_table );
    assert ( cardinal_max > 0 );

    /* initialize the kdtree */
    kdtree_to_create = init_kdtree ( kdtree_to_create );
    /* find the sectionnal axis */
    reference_axis = choice_reference_axis ( reference_table );
    /* find the cutting plan */
    reference_cutting = central_line_unsorted ( reference_table, 
                            reference_axis );
    width = get_color_table_width ( reference_table );

    /* set the sectionnal axis to the kdtree */
    set_kdtree_sectional_plan ( kdtree_to_create, reference_axis );
    /* set the cutting plan to the kdtree */
    set_kdtree_cutting_plan ( kdtree_to_create, reference_cutting );
    /* set the color table to the kdtree */
    set_kdtree_color_table ( kdtree_to_create, reference_table );

    /* exit condition for the creation of a kdtree */
    if ( cardinal_max <= width ) {
        /* updates the number of sons */ 
        height_kdtree = height_kdtree + 1;
        /* assigns his sons */
        assign_sons ( kdtree_to_create, cardinal_max );
    }
    return kdtree_to_create;
}

kdtree init_kdtree ( kdtree kdtree_to_init )
{
    /* allocate the kdtree */
    kdtree_to_init = malloc ( sizeof ( *kdtree_to_init ) );
    /* initialize the kdtree's variables */
    kdtree_to_init->kdTable = NULL;
    kdtree_to_init->left_son = NULL;
    kdtree_to_init->right_son = NULL;
    kdtree_to_init->cuttingPlan = 0;
    kdtree_to_init->sectionalAxis = 0;
    return kdtree_to_init;
}

axis get_kdtree_sectional_axis ( kdtree reference_kdtree )
{
    assert ( reference_kdtree );
    return reference_kdtree->sectionalAxis;
}

float get_kdtree_cutting_plan ( kdtree reference_kdtree )
{
    assert ( reference_kdtree );
    return reference_kdtree->cuttingPlan;
}

color_table get_kdtree_table_color ( kdtree reference_kdtree )
{
    assert ( reference_kdtree );
    return reference_kdtree->kdTable;
}

kdtree get_kdtree_left_son ( kdtree parent_kdtree )
{
    assert ( parent_kdtree );
    return parent_kdtree->left_son;
}

kdtree get_kdtree_right_son ( kdtree parent_kdtree )
{
    assert ( parent_kdtree );
    return parent_kdtree->right_son;
}

void set_kdtree_sectional_plan ( kdtree kd_reference, axis set_sectional )
{
    assert ( kd_reference );
    assert ( set_sectional >= 0 && set_sectional <= 2 );
    kd_reference->sectionalAxis = set_sectional;
}

void set_kdtree_cutting_plan ( kdtree kd_reference, float set_cutting )
{
    assert ( kd_reference );
    assert ( set_cutting >= 0 && set_cutting <= 255 );
    kd_reference->cuttingPlan = set_cutting;
}

void set_kdtree_color_table ( kdtree reference_kdtree, 
    color_table reference_table )
{
    assert ( reference_kdtree );
    assert ( reference_table );
    reference_kdtree->kdTable = reference_table;
}

void set_kdtree_left_son ( kdtree parent_kdtree, kdtree left_son_kdtree )
{
    assert ( parent_kdtree );
    assert ( left_son_kdtree );
    parent_kdtree->left_son = left_son_kdtree;
}

void set_kdtree_right_son ( kdtree parent_kdtree, kdtree right_son_kdtree )
{
    assert ( parent_kdtree );
    assert ( right_son_kdtree );
    parent_kdtree->right_son = right_son_kdtree;
}

static axis choice_reference_axis ( color_table reference_table )
{
    axis reference_axis;
    color delta_R[DIM]; /* The variation of the projections on each axis */
    color min_R[DIM]; /* The minimum rate of colors on each axis */
    color max_R[DIM]; /* The maximum rate of colors on each axis */
    color tmp[DIM]; /* Temporary storage of color rates */
    color tmp_max; /* Temporary storage of a maximum color rate */
    int i;
    int width; /* of the reference_table */

    assert ( reference_table );

    width = get_color_table_width ( reference_table );

    for (i = 0; i < DIM; i++) {
        /* sorting of the color table on the i axis */
        color_table_sort ( reference_table, i );
        /* Takes the minimum rate on the i axis */
        color_table_get_color ( reference_table, 0, tmp); 
        /* Save the color rate of the i axis */
        min_R[i] = tmp[i];
        /* Takes the maximum rate on the i axis */
        color_table_get_color ( reference_table, width - 1, tmp );
        /* Save the color rate of the i axis */
        max_R[i] = tmp[i];
    }
    /* Color rate difference */
    for ( i = 0; i < DIM; i++) { delta_R[i] = max_R[i] - min_R[i]; }
    /* 
     * Compares the variation of color rates and founds the axis associated 
     * with the largest variation a.k.a. The largest projection
     */ 
    if ( delta_R[0] >= delta_R[1] ) {
        tmp_max = delta_R[0];
        reference_axis = red;
    } else {
        tmp_max = delta_R[1];
        reference_axis = green;
    }
    if ( delta_R[2] >= tmp_max ) {
        reference_axis = blue;
    }
    return reference_axis;
}

static float central_line_sorted ( color_table reference_table, axis reference_axis )
{
    /* saves the pixels associated for the calculce of the midpoint */
    color central_line_pixel[2 * DIM]; 
    int width_table; /* of the reference_table */ 

    assert ( reference_table );
    assert ( reference_axis >= 0 && reference_axis <= 2 );

    width_table = get_color_table_width ( reference_table );
    /* 
     * If the width of the table is odd, 
     * then it is the pixel in the middle of the table
     */ 
    if ( width_table % 2 == 1 ) {
        color_table_get_color ( reference_table, ( width_table - 1 ) / 2, 
            central_line_pixel );
        return ( float ) central_line_pixel[reference_axis];
    }
    /* else it is the average of the two central pixels */
    color_table_get_color ( reference_table, width_table / 2 - 1, 
        central_line_pixel );
    color_table_get_color ( reference_table, width_table / 2, 
        central_line_pixel + 3 );
    return ( ( float ) ( central_line_pixel[reference_axis] + 
        central_line_pixel[reference_axis + DIM] ) / 2. );
}

static float central_line_unsorted ( color_table reference_table, 
    axis reference_axis )
{
    assert ( reference_table );
    assert ( reference_axis >= 0 && reference_axis <= 2);
    /* sort the table before the call in compare to the cutting axis */
	color_table_sort ( reference_table, reference_axis );
	return central_line_sorted ( reference_table, reference_axis );
}

void split_color_table ( kdtree reference_kdtree, color_table* inferior_table,
     color_table* superior_table )
{
    color_table kdtree_color_table = NULL;
    float reference_cutting;
    color* kdtree_table; /* the color table of the reference kd-tree */
    axis reference_axis;
    int width; /* of the reference table */
    /* 
     * the maximum index where the color rates 
     * of the table are lower than the cutting plan
     */
    int index; 

    assert ( reference_kdtree );
    assert ( inferior_table );
    assert ( superior_table );

    index = 0;
    /* initializes the variables */
    reference_axis = get_kdtree_sectional_axis ( reference_kdtree );
    reference_cutting = get_kdtree_cutting_plan ( reference_kdtree );
    kdtree_color_table = get_kdtree_table_color ( reference_kdtree );
    width = get_color_table_width ( kdtree_color_table );
    kdtree_table = get_color_table_tab ( kdtree_color_table, 0);

    while ( reference_cutting > kdtree_table[DIM * index + reference_axis] ) {
        index++; /* set the maximum index */
    }
    /* 
     * associates the sub-table with the pixels from 0 
     * to the maximum index -1 
    */
    *inferior_table = color_table_duplicate ( kdtree_color_table, 0, index );
    /* 
     * associates the sub-table with the pixels from the maximum index 
     * to the width of the table
    */
    *superior_table = color_table_duplicate ( kdtree_color_table, index, 
        width - index );
}

static void assign_sons ( kdtree parent_kdtree, int cardinal_max )
{
    /* defines the future color tables for the sons of the parent kdtree */
    color_table left_table;
    color_table right_table;
    /* defines the future kdtree sons of the parent kdtree */
    kdtree left_kdtree;
    kdtree right_kdtree;

    assert ( parent_kdtree );
    assert ( cardinal_max > 0 );
    /* assigns the color tables of the sons kdtree */
    split_color_table ( parent_kdtree, &left_table, &right_table );

    left_kdtree = create_kdtree ( left_table, cardinal_max );
    /* assigns the new kdtree to the parent */
    set_kdtree_left_son ( parent_kdtree, left_kdtree );

    right_kdtree = create_kdtree ( right_table, cardinal_max );
    set_kdtree_right_son ( parent_kdtree, right_kdtree );
}

void kdtree_get_nearest_color ( kdtree parent_kdtree,
    color reference_color[DIM], color buf[DIM] )
{
    axis reference_axis;
    float reference_cutting;

    axis left_axis; /* cutting axis of the left son */
    axis right_axis; /* right one */
    float left_cutting; /* cutting plan of the left son */
    float right_cutting; /* right one */
    /* 
     * difference between the cutting plan
     * and the reference pixel according to the cutting axis
     */
    float left_ptr; 
    float right_ptr; /* right one */
    /*
     * the saver buffer of the nearest pixel to the reference one, 
     * kept even during the recursive ascent
     */
    static save_pixel save_buf;
    /*
     * The rank associated with the current worksheet
     * 0 represents the sheet with the highest level
     * height_kdtree represents the sheet with the lowest level
     * kept even during the recursive ascent
     */
    static int rang_sheet = 0;
    /*
     * The path traveled during the descent,
     * and the recursive ascent in the tree
     * Left or Right
     */
    static status_son* previous_son;

    int i;

    assert ( parent_kdtree );
    assert ( reference_color );
    assert ( buf );

    if ( rang_sheet == 0 ) {
        /* Allocate according to the total number of sons */
        previous_son = calloc ( sizeof ( status_son ), height_kdtree );
        /* Initialize the lenth */
        save_buf.lenth = 1000;
    }
    /* Stop condition for the lowest level sheet */
    if ( get_kdtree_left_son ( parent_kdtree ) == NULL ) {
        if ( get_kdtree_right_son ( parent_kdtree ) != NULL ) {
            /*
             * retrieves the nearest pixel in the kdarbre table,
             * puts it in the buffer
             */
            get_color_table_rec_proxy_pixel ( get_kdtree_table_color ( 
                get_kdtree_right_son ( parent_kdtree ) ), reference_color, 
                &save_buf );
        }
    }
    if ( get_kdtree_right_son ( parent_kdtree ) == NULL ) {
        if ( get_kdtree_left_son ( parent_kdtree ) != NULL ) {
            get_color_table_rec_proxy_pixel ( get_kdtree_table_color ( 
                get_kdtree_left_son ( parent_kdtree ) ), reference_color, 
                &save_buf );
        } else {
            get_color_table_rec_proxy_pixel ( get_kdtree_table_color ( 
                parent_kdtree ), reference_color, &save_buf );
        }
    } else {
        /* 
         * defines the distance between the reference pixel 
         * and the cutting planes of the sons
         */
        left_axis = get_kdtree_sectional_axis ( get_kdtree_left_son ( parent_kdtree ) );
        right_axis = get_kdtree_sectional_axis ( get_kdtree_right_son ( parent_kdtree ) );

        left_cutting = get_kdtree_cutting_plan ( get_kdtree_left_son ( parent_kdtree ) );
        right_cutting = get_kdtree_cutting_plan ( get_kdtree_right_son ( parent_kdtree ) );

        left_ptr = fabs ( ( float ) reference_color[left_axis] - left_cutting );
        right_ptr = fabs ( ( float ) reference_color[right_axis] - right_cutting );
        /* defines the right path to travel in the kdtree */
        if ( left_ptr >= right_ptr ) {
            previous_son[rang_sheet] = right; /* update the path */
            rang_sheet++; /* update the rank : +1 -> descent */
            /* continues the journey */
            kdtree_get_nearest_color ( get_kdtree_right_son ( parent_kdtree ), reference_color, buf );
        } else {
            previous_son[rang_sheet] = left;
            rang_sheet++;
            kdtree_get_nearest_color ( get_kdtree_left_son ( parent_kdtree ), reference_color, buf );
        }
    }
    /* to be sure that the kdtree has sons */ 
    if ( ( get_kdtree_left_son ( parent_kdtree ) != NULL ) || ( get_kdtree_right_son ( parent_kdtree ) != NULL ) ) {
        rang_sheet--; /* update the rank : -1 -> ascent */
        reference_axis = get_kdtree_sectional_axis ( parent_kdtree );
        reference_cutting = get_kdtree_cutting_plan ( parent_kdtree );
        /* if the ray exceeds the cutting plane, the journey must continues */
        if ( reference_color[reference_axis] + save_buf.lenth > reference_cutting ) {
            if ( previous_son[rang_sheet] == left ) {
                previous_son[rang_sheet] = right;
                rang_sheet++;
                kdtree_get_nearest_color ( get_kdtree_right_son ( parent_kdtree ), reference_color, buf );
                rang_sheet--;
            } else {
                previous_son[rang_sheet] = left;
                rang_sheet++;
                kdtree_get_nearest_color ( get_kdtree_left_son ( parent_kdtree ), reference_color, buf );
                rang_sheet--;
            }
        }
    }
    if ( rang_sheet == 0 ) {
        free ( previous_son );
        for ( i = 0; i < DIM; i++ ) {
            buf[i] = save_buf.pixel[i];
            save_buf.pixel[i] = 0;
        }
    } /* update the variables */
}

boolean destroy_kdtree ( kdtree kdtree_to_destroy )
{
    assert ( kdtree_to_destroy );
    /* destroy the kdtree's left son */
    if ( get_kdtree_left_son ( kdtree_to_destroy )  != NULL ) {
        destroy_kdtree ( get_kdtree_left_son ( kdtree_to_destroy ) );
        free ( get_kdtree_left_son ( kdtree_to_destroy ) );
    }
    /* destroy the kdtree's right son */
    if ( get_kdtree_right_son ( kdtree_to_destroy ) != NULL ) {
        destroy_kdtree ( get_kdtree_right_son ( kdtree_to_destroy ) );
        free ( get_kdtree_right_son ( kdtree_to_destroy ) );
    }
    /* 
     * destroy the kdtree's root only if it is the highest level kdtree
     * Otherwize it will be destroyed by his parent kdtree
     * Means that it is a left son or a right son
     */
    if ( get_color_table_owner ( get_kdtree_table_color ( kdtree_to_destroy ) ) == true ) {
        /* destroy the kdtree's table color */
        destroy_color_table ( get_kdtree_table_color ( kdtree_to_destroy ) );
        /* destroy the kdtree's root */
        free ( kdtree_to_destroy );
    } else {
        /* destroy the kdtree's table color */
        destroy_color_table ( get_kdtree_table_color ( kdtree_to_destroy ) );
    }
    return true;
}