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
 * @file trivial_main.c
 * @brief the switch of the color.
 */

/**
 * @author STEIMETZ Tangui <steimetz.tangui@ecole.ensicaen.fr>
 * @author PICQUE Kylian <picque.kylian@ecole.ensicaen.fr>
 * @version 1.8.0
 * @date 02 janvier 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "table.h"
#include "image.h"
#include "color_switch.h"


int main ( int argc, char ** argv) 
{
	image futur_table;
	image futur_image;
	image image_last;

	color_table color_table1;

	char* new_name_image;
	int test;

    double time_search;
    clock_t begin;
    clock_t end;

	new_name_image = ( char* ) malloc( 50 * sizeof ( char ) );

	assert ( argc == 3 );
	assert ( argv[1] );
	assert( argv[2] );
	

	futur_table = init_image ( argv[2] );
	futur_image = init_image ( argv[1] );
	color_table1 = create_color_table ( futur_table );

	begin = clock (); /* __START_TIMER__ */
	image_last = color_switch_trivial ( futur_image, color_table1 );
	end = clock (); /* __END_TIMER__ */

	name_new_image_table ( argv[1], argv[2], new_name_image ); /*generates a name for the new picture*/ 
	test = image_sauvegarder ( image_last, new_name_image );
	if ( test == -1 ) { /*tests if the safeguarding succeeded */
		printf ( "an error happend\n" );
	}

    time_search = ( double ) ( end - begin ) / CLOCKS_PER_SEC;
    printf ( "%.5f %d\n", time_search, get_color_table_width ( 
		color_table1 ) ); /* displays the execution time, table length */

	free ( new_name_image ); /* begin variable liberation */
	destroy_color_table ( color_table1 );
	DEFAIRE_image ( image_last );
	DEFAIRE_image ( futur_table );
	DEFAIRE_image ( futur_image );

	return 0;
}
