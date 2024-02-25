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
 * @file kdtree_main.c
 * @brief the switch of the color with the kdtree method.
 */

/**
 * @author STEIMETZ Tangui <steimetz.tangui@ecole.ensicaen.fr>
 * @author PICQUE Kylian <picque.kylian@ecole.ensicaen.fr>
 * @version 1.9.0
 * @date 02 janvier 2022
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "table.h"
#include "kdtree.h"
#include "image.h"
#include "color_switch.h"


int main ( int argc, char* argv[3] )
{
	image futur_table;
	image futur_image;
	image image_last;

	color_table color_table1;

    kdtree kdtree;
    int card_max;
	float pourc;

	char* new_name_image;
	int test;

    double time_search;
    clock_t begin;
    clock_t end;

	assert ( argc == 4 );
	assert ( argv[1] );
	assert ( argv[2] );
	assert ( argv[3] );

	new_name_image = ( char* ) malloc ( 50 * sizeof ( char ) );

	pourc = 1000.;
	if ( strlen ( argv[3] ) == 1 ) { 
		pourc = *argv[3] - 48;
	} if ( strlen ( argv[3] ) == 2 ) {
		pourc = ( argv[3][0] - 48) * 10 + ( argv[3][1] - 48 );
	} if ( strlen ( argv[3] ) == 3 ) {
		pourc = ( argv[3][0] - 48) * 100 + ( argv[3][1] - 48 ) * 10 + ( argv[3][0] - 48 );
	}
	assert ( pourc > 0. && pourc <= 999. ); /* tests the cardinal value */
	pourc = pourc / 1000.;


	futur_table = init_image ( argv[2] );
	futur_image = init_image ( argv[1] );

	color_table1 = create_color_table ( futur_table );
    card_max = ( int ) ( pourc * ( float ) get_color_table_width ( color_table1 ) );
    kdtree = create_kdtree ( color_table1, card_max );

    begin = clock (); /* __START_TIMER__ */
	image_last = color_switch_kdtree ( futur_image, kdtree );
    end = clock (); /* __END_TIMER__ */

	name_new_image_tree ( argv[1] ,argv[2], new_name_image);/*generates a name for the new picture*/ 
	test = image_sauvegarder ( image_last, new_name_image);
	if (test == -1) {/*tests if the safeguarding succeeded */
		printf("an error happend");
	}

    time_search = ( double ) ( end - begin ) / CLOCKS_PER_SEC;
    printf ( "%.5f %d %d\n", time_search, get_color_table_width ( 
		get_kdtree_table_color ( kdtree ) ), card_max );/* displays the execution time, table length and the cardinal */

	free ( new_name_image );/* begin variable liberation */
	destroy_kdtree ( kdtree );
	DEFAIRE_image (image_last);
	DEFAIRE_image (futur_table);
	DEFAIRE_image (futur_image);
    

    return 0;
}