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

#include "color_switch.h"
#include "kdtree.h"

image color_switch_trivial ( image changed_image, color_table reference_table ) 
{
	int i,j;
	image new_image;
	int dim = image_give_dim ( changed_image );
	int hauteur = image_give_hauteur ( changed_image );
	int largeur =image_give_largeur ( changed_image );
	save_pixel pixel_proxi;
	color pix1[DIM];

	assert ( dim ==1 || dim == 3 );
	assert ( changed_image );
	assert ( reference_table );

	new_image = copy_image_zero ( changed_image );
	
	for (i=0; i<hauteur; i++){
		for (j=0; j<largeur; j++){
			image_read_pixel ( changed_image, i, j, pix1 ); /*extracts image's pixels */
			get_color_table_it_proxy_pixel ( reference_table, pix1,  
				&pixel_proxi); /*gives the nearest image's pixel from the table*/
			/*write the table's pixel in the new image */ 
			image_write_pixel ( new_image, i, j, pixel_proxi.pixel ); 
		}
	}
	return new_image;
}

image color_switch_kdtree ( image changed_image, kdtree reference_kdtree ) 
{
	int i,j;
	image new_image;
	int dim = image_give_dim ( changed_image );
	int hauteur = image_give_hauteur ( changed_image );
	int largeur =image_give_largeur ( changed_image );
	color pixel_proxi[DIM];
	color pix1[DIM];

	assert ( dim ==1 || dim == 3 );
	assert ( changed_image );
	assert ( reference_kdtree );

	new_image = copy_image_zero ( changed_image );
	
	for (i=0; i<hauteur; i++){
		for (j=0; j<largeur; j++){
			image_read_pixel ( changed_image, i, j, pix1 );
			kdtree_get_nearest_color ( reference_kdtree, pix1, pixel_proxi );
			image_write_pixel ( new_image, i, j, pixel_proxi );
		}
	}
	return new_image;
}

void name_new_image_table ( char* original_name, char* table_name, char* new_name) {
	int i = 0;
	int original_way = 17;
	int table_way = 23;
	char temp[] = "./ressource/inv_picture/";
	char table_inv [] = "_inv_";
	int size_temp = strlen(temp); 
	int size_table = strlen(table_name);
	int size_original = strlen(original_name);
	int size_new = 0;
	int size_table_inv = strlen(table_inv);


	assert ( original_name );
	assert ( table_name );
	assert ( new_name );

	if ( original_name[0] == 46) { /* if the name starts by './' */
		original_way +=2;
	}
	if ( table_name[0] == 46) {
		table_way += 2;
	}
	for (i=0; i<size_temp; i++){
		new_name[i] = temp[i];
		size_new++;
	} /* write the path of the picture */
	i=0;
	while (i < (size_original - original_way -4)) {
		new_name[ size_new ] = original_name [ original_way + i ];
		size_new++;
		i++;
	} /*insertion of the original name's picture without the file extension and the path*/
	for (i=0; i<size_table_inv; i++) {
		new_name[size_new] = table_inv[i];
		size_new++;
	}
	/* insertion of   '_inv' */
	i =0; 
	while ( i< (size_table - table_way - 4)) {
		new_name[ size_new ] = table_name[ table_way + i+1];
		size_new++;
		i++;
	}/*add the table name without the file extension and the path */
	for (i=0; i<3; i++) {
		new_name[size_new + i] = original_name[ size_original -(3-i)];
	}
	size_new += 3;
	new_name = (char *) realloc( new_name, size_new*sizeof(char)+1);/* defines new length*/
	
}

void name_new_image_tree ( char* original_name, char* table_name, char* new_name) {
	int i = 0;
	int original_way = 17;
	int table_way = 23;
	char temp[] = "./ressource/inv_picture/";
	char tree [] = "_inv_tree";
	int size_temp = strlen(temp); 
	int size_original = strlen(original_name);
	int size_new = 0;
	int size_tree = strlen(tree);


	assert ( original_name );
	assert ( table_name );
	assert ( new_name );

	if ( original_name[0] == 46) {
		original_way +=2;
	}
	if ( table_name[0] == 46) {
		table_way += 2;
	}
	for (i=0; i<size_temp; i++){
		new_name[i] = temp[i];
		size_new++;
	} /* write the path of the picture*/
	i=0;
	while (i < (size_original - original_way -4)) {
		new_name[ size_new ] = original_name [ original_way + i ];
		size_new++;
		i++;
	} /* insertion of the original name's picture without the file extension and the path */
	for (i=0; i<size_tree; i++) {

		new_name[size_new] = tree[i];
		size_new++;
	}
	/* insertion of   '_inv_tree' */
	i = 6; 
	while ( table_name [i + table_way] != '.') {
		new_name[ size_new ] = table_name[ table_way + i];
		size_new++;
		i++;
	}
	/*add the table name without the file extension and the path */
	for (i=0; i<4; i++) {
		new_name[size_new + i] = original_name[ size_original -(4-i)];
	}
	size_new += 3;
	new_name = (char *) realloc( new_name, size_new*sizeof(char)+1);
}