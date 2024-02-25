
#include <stdio.h>
#include <stdlib.h>

#include "kdtree.h"
#include "table.h"
#include "image.h"
#include "third_party_function.h"

/**
 * @brief displays the kdtree's informations.
 * 
 * @param kdtree the kdtree to be shown. 
 * 
 * @return 
 */
static void displayKd ( kdtree kdtree )
{
    color_table table = NULL;
    color* tab = NULL;
    int width;
    axis axe;
    float plan;

    assert ( kdtree );

    table = color_table_duplicate ( get_kdtree_table_color ( kdtree ), 0,
        get_color_table_width ( get_kdtree_table_color ( kdtree ) ) );
    tab = get_color_table_tab ( table, 0 );
    axe = get_kdtree_sectional_axis ( kdtree );
    plan = get_kdtree_cutting_plan ( kdtree );
    width = get_color_table_width ( table );

    printf ( "width = %d\n", width );
    printf ( "axe = %d\n", axe );
    printf ( "plan = %.2f\n", plan );
    displayTab ( tab, width );

    destroy_color_table ( table );
}

/**
 * @brief displays 2 pixels with their names.
 * 
 * @param pix1 the first pixel.
 * @param pix2 the second pixel.
 * @param pix1_name the name of the first pixel.
 * @param pix2_name the name of the second pixel.
 * 
 * @return 
 */
static void displayDoublePix ( color* pix1, char* pix1_name, color* pix2, 
    char* pix2_name ) 
{
    assert ( pix1 );
    assert ( pix2 );
    assert ( pix1_name );
    assert ( pix2_name );

    printf ( "%s : ", pix1_name );
    printf ( "[%d, %d, %d]\n", pix1[0], pix1[1], pix1[2] );
    printf ( "%s : ", pix2_name );
    printf ( "[%d, %d, %d]\n\n", pix2[0], pix2[1], pix2[2] );
}

int main ( void )
{
    image futur_table;
    color_table table = NULL;
    color_table sub_table = NULL;
    char *file_name = "./ressource/IMAGES/TABLES/table_fille_128.ppm";
    int width;
    int offset;

    kdtree ref_kdtree = NULL;
    int cardinal_max ;

    kdtree l1 = NULL;
    kdtree l2 = NULL;
    kdtree l3 = NULL;

    kdtree d1 = NULL;
    kdtree d2 = NULL;
    kdtree d3 = NULL;

    color exemple_pixel[3] = {50, 50, 50};
    color nearest_pixel[3] = {0};

    futur_table = init_image ( file_name );

    table = create_color_table ( futur_table );

    width = 50;
    offset = 10;
    sub_table = color_table_duplicate ( table, offset, width );
    cardinal_max = ( int ) ( 0.4 * ( float ) get_color_table_width ( sub_table ) );
    ref_kdtree = create_kdtree ( sub_table, cardinal_max );

    l1 = get_kdtree_left_son ( ref_kdtree );
    d1 = get_kdtree_right_son ( ref_kdtree );

    printf("\n\nEtape de construction kdtree, avec cardinal max = %d\n", 
        cardinal_max 
        );

    printf ( "Noeud 1er, ultime :\n" );
    displayKd ( ref_kdtree );
    printf ( "\nNoeud A :\n" );
    displayKd ( l1 );
    printf ( "Noeud B :\n" );
    displayKd ( d1 );

    l2 = get_kdtree_left_son ( l1 );
    d2 = get_kdtree_right_son ( l1 );

    printf ( "\nNoeud A1 :\n" );
    displayKd ( l2 );
    printf ( "Noeud A2 :\n");
    displayKd ( d2 );

    l3 = get_kdtree_left_son ( d1 );
    d3 = get_kdtree_right_son ( d1 );

    printf ( "\nNoeud B1 :\n" );
    displayKd ( l3 );
    printf ( "Noeud B2 :\n" );
    displayKd ( d3 );

    printf ( "\n\nTest nearest pixel of example : \n" );

    kdtree_get_nearest_color ( ref_kdtree, exemple_pixel, nearest_pixel );
    displayDoublePix ( exemple_pixel, "Example", nearest_pixel, "Nearest" );

    exemple_pixel[0] = 100; exemple_pixel[1] = 100; exemple_pixel[2] = 100; 
    kdtree_get_nearest_color ( ref_kdtree, exemple_pixel, nearest_pixel );
    displayDoublePix ( exemple_pixel, "Example", nearest_pixel, "Nearest" );

    exemple_pixel[0] = 150; exemple_pixel[1] = 150; exemple_pixel[2] = 150;    
    kdtree_get_nearest_color ( ref_kdtree, exemple_pixel, nearest_pixel );
    displayDoublePix ( exemple_pixel, "Example", nearest_pixel, "Nearest" );

    exemple_pixel[0] = 200; exemple_pixel[1] = 200; exemple_pixel[2] = 200;    
    kdtree_get_nearest_color ( ref_kdtree, exemple_pixel, nearest_pixel );
    displayDoublePix ( exemple_pixel, "Example", nearest_pixel, "Nearest" );

    exemple_pixel[0] = 250; exemple_pixel[1] = 250; exemple_pixel[2] = 250;    
    kdtree_get_nearest_color ( ref_kdtree, exemple_pixel, nearest_pixel );
    displayDoublePix ( exemple_pixel, "Example", nearest_pixel, "Nearest" );

    destroy_color_table ( table );
    destroy_kdtree ( ref_kdtree );

    DEFAIRE_image ( futur_table );

    return 0;
}