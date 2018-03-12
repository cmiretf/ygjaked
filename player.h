/** 
 * @file player.h
 * @author Miguel Ángel Liaño y Carlos Miret Fiuza
 * @version 1.0 
 * @date 10-2-2018 
 * @copyright GNU Public License
 */
#ifndef PLAYER_H
#define PLAYER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

/*Se definen las distintas características que puede poseer un player en el juego*/
typedef struct _Player Player;

/*
 * @author Miguel Ángel Liaño
 * @brief Inicializa un player pasado como parametro
 * @param id, de tipo Id (definida en types.h)
 * @return NULL en caso de error, y en caso válido, devuelve un puntero a Player
 */
Player* player_create(Id id);

/*
 * @author Miguel Ángel Liaño
 * @brief Borra un player pasado como argumento
 * @param player, de tipo Player (definida en player.h, e implementada en este archivo)
 * @return ERROR en caso de error, y en caso válido, devuelve OK
 */
STATUS player_destroy(Player* player);

/*
 * @author Miguel Ángel Liaño
 * @brief Establece el nombre pasado por argumento a un player pasado por argumentos
 * @param player, de tipo Player y @param char (haciendo alusion al nombre)
 * @return ERROR en caso de ser el mismo nombre(el de la estructura Player, 
 *	y el pasado como parametro), y en caso válido, devuelve OK
 */
STATUS player_set_name(Player* player, char* name);

/*
 * @author Miguel Ángel Liaño
 * @brief Establece la direccion dada por argumento a un player pasado por argumento
 * @param player, de tipo Player jugador al que asignarle una direccion
 * @param id , futuro identificador del jugador 
 * @return ERROR en caso de error en los argumentos, y en caso válido, devuelve OK
 */
STATUS player_set_id(Player* player, Id id);

/*
 * @author Miguel Ángel Liaño
 * @brief Establece un objeto pasado por argumento a un player pasado como argumento
 * @param player, de tipo Player y @param value de tipo BOOL
 * @return ERROR en caso no encontrar player, en caso valido, devuelve OK
 */
STATUS player_set_object_id(Player* player, Id vid);

/*
 * @author Miguel Ángel Liaño
 * @brief Devuelve el nombre de un player pasado como argumento
 * @param player, de tipo Player
 * @return NULL en caso no encontrar player, en caso valido devuelve char
 */
const char * player_get_name(Player* player);

/*
 * @author Miguel Ángel Liaño
 * @brief Devuelve la dirección de un player pasado como agumento
 * @param player, de tipo Player
 * @return NO_ID en caso no encontrar player, en caso valido devuelve variable de tipo Id
 */
Id player_get_id(Player* player);

/*
 * @author Miguel Ángel Liaño
 * @brief Comprueba si el jugador dado como argumento tiene objeto
 * @param player, de tipo Player
 * @return FALSE en caso no no encontrar player y devuelve un objeto de la estructura espacio
 */
Id player_get_object_id(Player* player);

/*
 * @author Miguel Ángel Liaño
 * @brief Imprime los datos, del player pasado como argumento (nombre, dirección, norte, sur, si hay un objeto...)
 * @param player, de tipo Player
 * @return ERROR en caso no no encontrar player y devuelve OK en caso válido
 */
STATUS player_print(Player* player);
#endif /*PLAYER_H*/
