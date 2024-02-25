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
 * @file third_party_function.c
 * @brief Prototypes of functions used for third_party_function's algorithm.
 */

/**
 * @author STEIMETZ Tangui <steimetz.tangui@ecole.ensicaen.fr>
 * @author PICQUE Kylian <picque.kylian@ecole.ensicaen.fr>
 * @version 3.0.0
 * @date 28 decembre 2021
 */ 

#include <stdio.h>
#include <stdlib.h>

#include "third_party_function.h"

image init_image ( char* file_name ) 
{
	image image_to_init;

    assert ( file_name );
	
    image_to_init = FAIRE_image (); 
    image_debut ( image_to_init ); 
    image_charger ( image_to_init, file_name ); /*transfers the picture in the image variable*/

	return image_to_init;
}

image copy_image_zero ( image original_img )
{
    int dim;
    int hauteur;
    int largeur;
    image copy_img; 

    assert ( original_img );

    dim = image_give_dim ( original_img );
    hauteur = image_give_hauteur ( original_img );
    largeur = image_give_largeur ( original_img );
	
    copy_img = FAIRE_image ();
    image_debut ( copy_img );
    /* gives the same features to the new image */
    image_initialize ( copy_img, dim, largeur, hauteur ); 
    image_debut ( copy_img );

	return copy_img;
}

void displayTab ( unsigned char* tab, int size )
{
    int i;

    assert ( tab );
    assert ( size );

    printf ( "display\n" );
    printf ("[");
    for ( i = 0; i < size * DIM; i++ ) {
        printf ( "%d ", tab[i] );
        if ( ( ( i + 1 ) % DIM == 0) && ( i != 0) ) {
            printf ( "] [" );
        }
    }
    printf ( "]\n" );
}

void displayTabOnAxis ( unsigned char* tab, int size, axis ref_axis )
{
    int i;

    assert ( tab );
    assert ( size );
    assert ( ref_axis >= 0 && ref_axis <= 2 );

    printf ( "display on axis\n[" );
    for ( i = 0; i < size; i++ ) {
        printf("%d, ", tab[i * DIM + ref_axis] );
    }
    printf ( "]\n" );
}