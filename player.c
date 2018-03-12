/** 
 * @brief La tarea principal es definir la existencia o no de un jugador en el mapa y las direcciones del mismo
 * 
 * @file player.c
 * @author Miguel Ángel Liaño
 * @version 1.0 
 * @date 10-2-2018 
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
struct _Player {
  Id id; /*Dirección de un player*/
  char name[WORD_SIZE + 1]; /*Nombre del player*/
  Id object; /*Direccion del objeto en el player*/
  Id player_location;/*Localizacion del jugador en el juego*/
};
/*
 * @author Miguel Ángel Liaño
 * @brief Inicializa un player pasado como parametro
 * @param id, de tipo Id (definida en types.h)
 * @return NULL en caso de error, y en caso válido, devuelve un puntero a Player
 */
Player* player_create(Id id) {

  Player *newPlayer = NULL;

  if (id == NO_ID)
    return NULL;

  newPlayer = (Player *) malloc(sizeof (Player));

  if (newPlayer == NULL) {
    return NULL;
  }
  newPlayer->id = id;

  newPlayer->name[0] = '\0';
  newPlayer->object = FALSE;

  return newPlayer;
}

/*
 * @author Miguel Ángel Liaño
 * @brief Borra un player pasado como argumento
 * @param player, de tipo Player (definida en player.h, e implementada en este archivo)
 * @return ERROR en caso de error, y en caso válido, devuelve OK
 */
STATUS player_destroy(Player* player) {
  if (!player) {
    return ERROR;
  }

  free(player);
  player = NULL;

  return OK;
}

/*
 * @author Miguel Ángel Liaño
 * @brief Establece el nombre pasado por argumento a un player pasado por argumentos
 * @param player, de tipo Player y @param char (haciendo alusion al nombre)
 * @return ERROR en caso de ser el mismo nombre(el de la estructura Player, 
 *	y el pasado como parametro), y en caso válido, devuelve OK
 */
STATUS player_set_name(Player* player, char* name) {
  if (!player || !name) {
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }

  return OK;
}
/*
 * @author Miguel Ángel Liaño
 * @brief Establece la direccion dada por argumento a un player pasado por argumento
 * @param player, de tipo Player jugador al que asignarle una direccion
 * @param id , futuro identificador del jugador 
 * @return ERROR en caso de error en los argumentos, y en caso válido, devuelve OK
 */
STATUS player_set_id(Player* player, Id id){
  if (player == NULL || id == NO_ID)
    return ERROR;

  player->id = id;
 
  return OK;
}


/*
 * @author Miguel Ángel Liaño
 * @brief Establece un objeto pasado por argumento a un player pasado como argumento
 * @param player, de tipo Player y @param value de tipo BOOL
 * @return ERROR en caso no encontrar player, en caso valido, devuelve OK
 */
STATUS player_set_object_id(Player* player,Id id) {
  if (!player) {
    return ERROR;
  }
  player->object = id;
  return OK;
}

/*
 * @author Miguel Ángel Liaño
 * @brief Devuelve el nombre de un player pasado como argumento
 * @param player, de tipo Player
 * @return NULL en caso no encontrar player, en caso valido devuelve char
 */
const char * player_get_name(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->name;
}

/*
 * @author Miguel Ángel Liaño
 * @brief Devuelve la dirección de un player pasado como agumento
 * @param player, de tipo Player
 * @return NO_ID en caso no encontrar player, en caso valido devuelve variable de tipo Id
 */
Id player_get_id(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->id;
}

/*
 * @author Miguel Ángel Liaño
 * @brief Devuelve el objeto de un player pasado como argumento
 * @param player, de tipo Player
 * @return FALSE en caso no no encontrar player y devuelve un objeto de la estructura espacio
 */
Id player_get_object_id(Player* player) {
  if (!player) {
    return FALSE;
  }
  return player->object;
}

/*
 * @author Miguel Ángel Liaño
 * @brief Imprime los datos, del player pasado como argumento (nombre, dirección, norte, sur, si hay un objeto...)
 * @param player, de tipo Player
 * @return ERROR en caso no no encontrar player y devuelve OK en caso válido
 */
STATUS player_print(Player* player) {
  if (!player) {
    return ERROR;
  }

  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

  if (player_get_object_id(player)) {
    fprintf(stdout, "---> Object in the space.\n");
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}
