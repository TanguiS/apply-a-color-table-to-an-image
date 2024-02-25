SRC_PATH = ./src
OBJ_PATH = ./obj
BIN_PATH = ./bin
INC_PATH = ./include
LIB_PATH = ./lib
TEST_PATH = /TEST
RES_PATH = ./ressource
PICT_PATH = /inv_picture


#OBJS pour le test de table.c
OBJS_TABLE = $(OBJ_PATH)/test_table.o $(OBJ_PATH)/table.o $(OBJ_PATH)/third_party_function.o
#OBJS pour le test de kdtree.c
OBJS_KDTREE = $(OBJ_PATH)/test_kdtree.o $(OBJ_PATH)/kdtree.o $(OBJ_PATH)/table.o $(OBJ_PATH)/third_party_function.o
#OBJS pour l'inversion de couleurs méthode kdtree
OBJS_INV = $(OBJ_PATH)/kdtree_main.o $(OBJ_PATH)/kdtree.o $(OBJ_PATH)/table.o $(OBJ_PATH)/third_party_function.o $(OBJ_PATH)/color_switch.o
#OBJS pour l'inversion de couleurs méthode triviale
OBJS_TRIVIAL = $(OBJ_PATH)/trivial_main.o $(OBJ_PATH)/color_switch.o $(OBJ_PATH)/kdtree.o $(OBJ_PATH)/table.o $(OBJ_PATH)/third_party_function.o

CC = gcc
CPPFLAGS = -I$(INC_PATH) -L$(LIB_PATH)
LDFLAGS = $(LIB_PATH)/libimage.a
CFLAGS = -Wall -Wextra -ansi -pedantic -O3

#Macro pour créer l'exécutable pour le test de table.c
OUTPUT_TABLE = $(BIN_PATH)/test_table
#Macro pour créer l'exécutable pour le test de kdtree.c
OUTPUT_KDTREE = $(BIN_PATH)/test_kdtree
#Macro pour créer l'exécutable pour l'inversion de couleurs par recherche dans un kd-arbre
OUTPUT_INV = $(BIN_PATH)/kdtree_method
#Macro pour créer l'exécutable pour l'inversion de couleurs méthode triviale
OUTPUT_TRIVIAL = $(BIN_PATH)/trivial_method

#Appel aux macros des exécutables
all: inv tests 

trivial: $(OUTPUT_TRIVIAL)

kdtree: $(OUTPUT_INV)

inv: trivial kdtree

tests: $(OUTPUT_KDTREE) $(OUTPUT_TABLE)

#Création du fichier objet temporaire trivial_main.c
$(OBJ_PATH)/trivial_main.o: $(SRC_PATH)/trivial_main.c $(OBJ_PATH) $(INC_PATH)/table.h $(INC_PATH)/image.h $(RES_PATH)$(PICT_PATH)
	$(CC) $(CPPFLAGS) -c $(CFLAGS)  $< -o $@

#Création du fichier objet temporaire color_switch.c
$(OBJ_PATH)/color_switch.o: $(SRC_PATH)/color_switch.c $(INC_PATH)/color_switch.h $(OBJ_PATH) $(INC_PATH)/image.h $(INC_PATH)/table.h $(INC_PATH)/kdtree.h
	$(CC) $(CPPFLAGS) -c $(CFLAGS) $< -o $@
 
#Création du fichier objet temporaire table.c
$(OBJ_PATH)/table.o: $(SRC_PATH)/table.c $(INC_PATH)/table.h $(INC_PATH)/image.h $(OBJ_PATH)
	$(CC) $(CPPFLAGS) -c $(CFLAGS)  $< -o $@

#Création du fichier objet temporaire test_table.c
$(OBJ_PATH)/test_table.o: $(SRC_PATH)$(TEST_PATH)/test_table.c $(INC_PATH)/image.h $(INC_PATH)/table.h $(INC_PATH)/third_party_function.h $(OBJ_PATH) 
	$(CC) $(CPPFLAGS) -c $(CFLAGS)  $< -o $@

#Création du fichier objet temporaire test_kdtree.c
$(OBJ_PATH)/test_kdtree.o: $(SRC_PATH)$(TEST_PATH)/test_kdtree.c $(INC_PATH)/kdtree.h $(INC_PATH)/table.h $(INC_PATH)/image.h $(INC_PATH)/third_party_function.h $(OBJ_PATH)
	$(CC) $(CPPFLAGS) -c $(CFLAGS) $<  -o $@

#Création du fichier objet temporaire kdtree.c
$(OBJ_PATH)/kdtree.o: $(SRC_PATH)/kdtree.c $(INC_PATH)/kdtree.h $(INC_PATH)/table.h $(INC_PATH)/third_party_function.h $(OBJ_PATH) 
	$(CC) $(CPPFLAGS) -c $(CFLAGS) $<  -o $@ 

#Création du fichier objet temporaire kdtree_main.c
$(OBJ_PATH)/kdtree_main.o: $(SRC_PATH)/kdtree_main.c $(INC_PATH)/kdtree.h $(INC_PATH)/table.h $(OBJ_PATH) $(RES_PATH)$(PICT_PATH)
	$(CC) $(CPPFLAGS) -c $(CFLAGS) $<  -o $@

#Création du fichier objet temporaire third_party_function.c
$(OBJ_PATH)/third_party_function.o: $(SRC_PATH)/third_party_function.c $(INC_PATH)/third_party_function.h $(INC_PATH)/kdtree.h $(INC_PATH)/table.h $(OBJ_PATH)
	$(CC) $(CPPFLAGS) -c $(CFLAGS) $<  -o $@

#Création des dossiers de sorties de la compilation et des exécutables
$(OBJ_PATH):
	mkdir $@
$(BIN_PATH):
	mkdir $@
$(RES_PATH)$(PICT_PATH):
	mkdir $@

$(OUTPUT_TRIVIAL): $(OBJS_TRIVIAL) $(BIN_PATH) $(RES_PATH)$(PICT_PATH) #creation de trivial
	$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJS_TRIVIAL) -o $@ $(LDFLAGS)

$(OUTPUT_TABLE): $(OBJS_TABLE) $(BIN_PATH) #creation du test table
	$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJS_TABLE) -o $@ $(LDFLAGS)

$(OUTPUT_KDTREE): $(OBJS_KDTREE) $(BIN_PATH) #creation du test kdtree
	$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJS_KDTREE) -o $@ $(LDFLAGS)

$(OUTPUT_INV): $(OBJS_INV) $(BIN_PATH) $(RES_PATH)$(PICT_PATH) #creation de la methode inv de couleurs
	$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJS_INV) -o $@ $(LDFLAGS)

doxy:
	doxygen ./ressource/doc/doxyfile

clean: $(OBJ_PATH) #Détruire les fichiers temporaires
	rm -f $</*.o

#Retrouve le dossier de travail inital
distclean: $(OBJ_PATH) $(BIN_PATH) $(RES_PATH)$(PICT_PATH) 
	chmod u+x ./script/reset.sh
	./script/reset.sh ./script/data ./script/graph ./script
	rm -rf $< $(BIN_PATH) $(RES_PATH)$(PICT_PATH) ./ressource/doc/html

