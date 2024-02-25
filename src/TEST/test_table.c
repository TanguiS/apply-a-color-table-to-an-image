
#include <stdio.h>
#include <stdlib.h>

#include "table.h"
#include "image.h"
#include "third_party_function.h"

int main ( void ) 
{
    image futur_table;

    color_table table = NULL;
    color_table sub_table = NULL;
    char *file_name = "./ressource/IMAGES/TABLES/table_fille_128.ppm";
    color* tab = NULL;
    color* sub_tab = NULL;
    color* tri = NULL;
    int width;
    int sub_width;
    boolean owner;
    boolean sub_owner;

    boolean status;
    color rgb_table[3];
    int offset;
    int sub_offset;

    futur_table = init_image ( file_name );

    table = create_color_table ( futur_table );
    offset = 0;
    tab = get_color_table_tab ( table, offset );
    width = get_color_table_width ( table );
    owner = get_color_table_owner ( table );
  
    printf ( "\nCaractéristiques structure Table : \n");
    printf ( "Table width : %d\n", width );
    printf ( "Table owner : %d\n", owner );
    printf ( "Table color : " );
    displayTab ( tab, width - offset );
    tab = NULL;
    printf ( "\n\n" );

    sub_offset = 5;
    sub_width = 3;
    sub_table = color_table_duplicate ( table, sub_offset, sub_width);
    sub_tab = get_color_table_tab ( sub_table, offset );
    sub_owner = get_color_table_owner ( sub_table );

    printf ( "Caractéristiques structure sub_Table\n" );
    printf ( "sub_Table width : %d\n", sub_width );
    printf ( "sub_Table owner : %d\n", sub_owner );
    printf ( "sub_Table offset : %d\n", sub_offset );
    printf ( "sub_Table color : ");
    displayTab ( sub_tab, sub_width - offset );
    sub_tab = NULL;
    printf ( "\n\n" );
  
    color_table_get_color ( table, sub_offset, rgb_table );

    printf (
        "Récupération pixel d'un offset/index = %d de la table : ", 
        sub_offset
        );
    printf("%d %d %d\n", rgb_table[0], rgb_table[1], rgb_table[2]);
    printf ( "\n\n" );
  
    printf ( "Tri de sub_table :\n" );
    color_table_sort ( sub_table, red );
    tri = get_color_table_tab ( sub_table, offset );
    printf ( "Red sort : " );
    displayTab ( tri, sub_width );
    tri = NULL;

    printf ( "Green sort : " );
    color_table_sort ( sub_table, green );
    tri = get_color_table_tab ( sub_table, offset );
    displayTab ( tri, sub_width );
    tri = NULL;
  
    printf ( "Blue sort : " );
    color_table_sort ( sub_table, blue );
    tri = get_color_table_tab ( sub_table, offset );
    displayTab ( tri, sub_width );
    tri = NULL;
    printf ( "\n\n" );
  
    printf ( "Destruction des tables : \n" );
    status = destroy_color_table ( sub_table );
    printf ( "sub_Table destroy: %d\n", status );
    status = destroy_color_table ( table );
    printf ( "Table destroy: %d\n", status );


    DEFAIRE_image ( futur_table );
	return 0;
}
