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
 * @file table.c
 * @brief Functions of table's algorithm.
 */

/**
 * @author STEIMETZ Tangui <steimetz.tangui@ecole.ensicaen.fr>
 * @author PICQUE Kylian <picque.kylian@ecole.ensicaen.fr>
 * @version 3.0.0
 * @date 23 decembre 2021
 */ 

#include "table.h"

struct _color_table {
	color* table; /* table of colors */
	int width; /* size of the table */
	boolean owner; /* state of the color table */
};

color_table create_color_table ( image img_1D )
{  
	color_table create_table = NULL; /* the color table to create */
	int j;
	int img_width; /* the width of the image */
	int width; /* the width of the table */

	assert ( img_1D );

	/* initialize the table */
	create_table = init_color_table ( create_table );
	/* width of the 1 dim image */
	img_width = image_give_largeur ( img_1D );

	/* set owner to true */
	set_color_table_owner ( create_table, 1 ); 
	/* set width to img_width */
	set_color_table_width ( create_table, img_width );
	/* get width of the table */
	width = get_color_table_width ( create_table ); 
	
	/* allocate the table color */
	set_color_table_tab ( create_table, calloc ( sizeof ( color ), 
		img_width * DIM ), 0 );

	/* set the color tab */
	for ( j=0; j < width; j++ ) {
		image_read_pixel ( img_1D, 0, j, get_color_table_tab ( create_table
			, j ) );		
	}
	return create_table;
}

color_table init_color_table ( color_table table_to_init )
{
	assert ( sizeof ( table_to_init ) );
	table_to_init = malloc ( sizeof ( *table_to_init ) );
	table_to_init->table = NULL;
	table_to_init->width = 0;
	table_to_init->owner = 0;
	return table_to_init;
}

color* get_color_table_tab ( color_table reference_table, int offset )
{
	assert ( reference_table );
	assert ( offset >= 0 
		&& 
		offset <= get_color_table_width ( reference_table ) );
	return ( reference_table->table + 0 ) + offset * DIM;
}

void set_color_table_tab ( color_table reference_table, color* reference_tab, 
	int set_offset )
{
	assert ( reference_table );
	assert ( reference_tab );
	assert ( set_offset >= 0 );
	reference_table->table = ( reference_tab + 0 ) + set_offset * DIM;
}

boolean get_color_table_owner ( color_table reference_table )
{
	assert ( reference_table );
	return reference_table->owner;
}

void set_color_table_owner ( color_table reference_table, boolean set_owner )
{
	assert ( reference_table );
	assert ( set_owner >= 0 && set_owner <= 1 );
	reference_table->owner = set_owner;
}

int get_color_table_width ( color_table reference_table )
{
	assert ( reference_table );
	return reference_table->width;
}

void set_color_table_width ( color_table reference_table, int set_width )
{
	assert ( reference_table );
	assert ( set_width >= 0 );
	reference_table->width = set_width;
}

boolean destroy_color_table ( color_table table_to_destroy )
{
	assert ( table_to_destroy );
	if ( get_color_table_owner ( table_to_destroy ) == true ) {
		free ( get_color_table_tab ( table_to_destroy, 0 ) ); 
	}
	free ( table_to_destroy );
	return true;
}

color_table color_table_duplicate ( color_table reference_table, int offset, 
	int width_sub_table ) 
{
	color_table sub_color_table = NULL;

	assert ( reference_table );
	assert ( offset >= 0 
	&& 
	offset <= get_color_table_width ( reference_table ) );
	assert ( width_sub_table >= 0 
	&& 
	width_sub_table <= get_color_table_width ( reference_table ) );
	
	sub_color_table = init_color_table ( sub_color_table );
 
	set_color_table_owner ( sub_color_table, false );
  	set_color_table_width ( sub_color_table, width_sub_table ); 
	set_color_table_tab ( sub_color_table, 
		get_color_table_tab ( reference_table, 0 ), offset );
	return sub_color_table;
}

void color_table_get_color ( color_table reference_table, int index, 
	color buf[3] )
{
	int i;
	color* ptr;

	assert ( reference_table );
	assert ( index >= 0 
	&& 
	index <= get_color_table_width ( reference_table ) );
	assert ( buf );
		
	/* ptr points to the reference_table shifted of an index */
	ptr = get_color_table_tab ( reference_table, index ); 
	for ( i = 0; i < DIM; i++ ) {
		/* puts the pixel's rate into the buffer */ 
		buf[i] = ptr[i];
	}
}

int redComparator ( const void* first, const void* second )
{
    const color *firstRed = ( const color* ) first;
    const color *secondRed = (const color* ) second;
    return firstRed[0] - secondRed[0];
}

int greenComparator ( const void* first, const void* second )
{
    const color *firstGreen = ( const color* ) first;
    const color *secondGreen = ( const color* ) second;
    return firstGreen[1] - secondGreen[1];
}

int blueComparator ( const void * first, const void * second )
{
    const color *firstBlue = ( const color* ) first;
    const color *secondBlue = (const color* ) second;
    return firstBlue[2] - secondBlue[2];
}

void color_table_sort ( color_table reference_table, axis rgb_switch )
{
	int width;

	assert ( reference_table );
	assert ( rgb_switch >= 0 && rgb_switch <= 2 );

	width = get_color_table_width ( reference_table );

	/* sort according to the axis of rgb_switch */
    switch ( rgb_switch ) {
        case 0:
            qsort ( get_color_table_tab ( reference_table, 0 ), width , 
				DIM * sizeof ( color ), redComparator );
            break;
        case 1:
            qsort ( get_color_table_tab ( reference_table, 0 ), width , 
				DIM * sizeof ( color ), greenComparator );
            break;
        case 2:
            qsort ( get_color_table_tab ( reference_table, 0 ), width , 
				DIM * sizeof ( color ), blueComparator );
            break;
        default:
            break;
    }
}

int lenth_pixel ( color* pix1, color* pix2 ) 
{
	int sum = 0;
	int i; 
	for ( i = 0; i < DIM; i++ ) {
		sum += abs ( pix1[i] - pix2[i] );
	}
	return sum;
}

void get_color_table_it_proxy_pixel ( color_table reference_table, 
    color* reference_pixel, save_pixel* proxy_pixel )
{
    int h;
    save_pixel buf;
    int width = get_color_table_width ( reference_table );

    color_table_get_color ( reference_table, 0, proxy_pixel->pixel );
    proxy_pixel->lenth = lenth_pixel ( reference_pixel, proxy_pixel->pixel );

    for ( h = 1; h < width; h++ ) {
        color_table_get_color ( reference_table, h, buf.pixel );
        buf.lenth = lenth_pixel ( reference_pixel, buf.pixel );
        if ( buf.lenth < proxy_pixel->lenth ) { *( proxy_pixel ) = buf; }
    }
}

void get_color_table_rec_proxy_pixel ( color_table reference_table,
    color* reference_pixel, save_pixel* proxy_pixel )
    {
        int h;
        int i;
        save_pixel buf;
        int width = get_color_table_width ( reference_table );

        for ( h = 0; h < width; h++ ) {
            color_table_get_color ( reference_table, h, buf.pixel );
            buf.lenth = lenth_pixel ( reference_pixel, buf.pixel );
            if ( proxy_pixel->lenth > buf.lenth ) {
                proxy_pixel->lenth = buf.lenth;
                for ( i = 0; i < DIM; i++ ) { proxy_pixel->pixel[i] = buf.pixel[i]; }
            }
        }
}





































