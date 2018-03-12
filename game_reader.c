/* 
 * @brief Interpreta los elementos esenciales del juego
 * @file game_reader.c
 * @author Miguel Ángel Liaño y Carlos Miret Fiuza
 * @version 1.0 
 * @date 10-02-2018 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_reader.h"
#include "game.h"

/*
 * @author Miguel Ángel Liaño
 * @brief Carga los espacios del juego
 * @param game, Juego donde se añadirán los espacios
 * @param filename, Archivo con el contenido de los espacios 
 * @return Error si algunos de los argumentos son erróneos y OK si se consigue realizar correctamente la carga de los espacios
 */
STATUS gameReader_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space* space = NULL;
  STATUS status = OK;
  
  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
#ifdef DEBUG 
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      space = space_create(id);
      if (space != NULL) {
	space_set_name(space, name);
	space_set_north(space, north);
	space_set_east(space, east);
	space_set_south(space, south);
	space_set_west(space, west);
	game_add_space(game, space);
      }
    }
  }
  
  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  
  return status;
}
/*
 * @author Carlos Miret Fiuza
 * @brief Carga los objeto del juego
 * @param game, Juego donde se añadirán los objetos
 * @param filename, Archivo con el contenido de los espacios 
 * @return Error si algunos de los argumentos son erróneos y OK si se consigue realizar correctamente la carga de los objetos
 */
STATUS gameReader_load_objects(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id_location = NO_ID, id_object = NO_ID;
  Space* space = NULL;
  Object *object = NULL;
  STATUS status = OK;
  
  if (!filename) {
    return ERROR;
  }
  
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
  
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id_object = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      id_location=atol(toks);
#ifdef DEBUG 
      printf("Leido: %ld|%s|%ld\n", id_object, name, id_location);
#endif
      object = object_create(id_object, id_location);
      if (object != NULL) {
	object_set_name(object, name);
	game_add_object(game,object);
	space = game_get_space(game, id_location);
	space_add_object(space, id_object);
      }
    }
  }
  
  if (ferror(file)) {
    status = ERROR;
  }
  
  fclose(file);
  
  return status;
}
