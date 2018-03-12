/** 
 * @file space.h
 * @author Miguel Ángel Liaño y Carlos Miret Fiuza
 * @version 1.0 
 * @date 10-2-2018 
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "object.h"
#include "player.h"
#include "set.h"

typedef struct _Space Space;

/*Numero maximo de espacios en el mapa*/
#define MAX_SPACES 100

/*Primer espacio del juego*/
#define FIRST_SPACE 1

/*Distintas descripciones gráficas para los espacios del juego*/
#define MAX_GDESC 3

/*Tamaño maximo para dibujar las distintas descrpiciones graficas*/
#define TAM_GDESC 7
/*
 * @author Miguel Ángel Liaño
 * @brief Inicializa un espacio pasado como parametro
 * @param id, de tipo Id (definida en types.h)
 * @return NULL en caso de error, y en caso válido, devuelve un puntero a Space
 */
Space* space_create(Id id);

/*
 * @author Carlos Miret Fiuza
 * @brief Borra un espacio pasado como argumento
 * @param space, de tipo Space (definida en space.h, e implementada en este archivo)
 * @return ERROR en caso de error, y en caso válido, devuelve OK
 */
STATUS space_destroy(Space* space);

/*
 * @author Miguel Ángel Liaño
 * @brief Devuelve la dirección de un espacio pasado como agumento
 * @param space, de tipo Space
 * @return NO_ID en caso no encontrar espacio, en caso valido devuelve variable de tipo Id
 */
Id space_get_id(Space* space);

/*
 * @author Carlos Miret Fiuza
 * @brief Establece el nombre pasado por argumento a un espacio pasado por argumentos
 * @param space, de tipo Space y @param char (haciendo alusion al nombre)
 * @return ERROR en caso de ser el mismo nombre(el de la estructura space, 
 *	y el pasado como parametro), y en caso válido, devuelve OK
 */
STATUS space_set_name(Space* space, char* name);

/*
 * @author Miguel Ángel Liaño 
 * @brief Establece las distintas descripciones gráficas para los espacios del juego
 * @param space, de tipo Space y @param char (haciendo alusion al nombre)
 * @return ERROR si el espacio dado es incorrecto o si no se detecta la palabra claves gdesc, y en caso válido, devuelve OK
 */
STATUS space_set_gdesc(Space *space, char *gdesc);
/*
 * @author Miguel Ángel Liaño
 * @brief Devuelve el nombre de un espacio pasado como argumento
 * @param space, de tipo Space
 * @return NULL en caso no encontrar espacio, en caso valido devuelve char
 */
const char* space_get_name(Space* space);

/*
 * @author Carlos Miret Fiuza
 * @brief Establece la coordenada norte pasada por argumento a un espacio pasado como argumento
 * @param space, de tipo Space y @param id de tipo Id
 * @return ERROR en caso no encontrar espacio o no id, en caso valido, devuelve OK
 */
STATUS space_set_north(Space* space, Id id);

/*
 * @author Miguel Ángel Liaño
 * @brief Devuelve la coordenada norte de un espacio pasado como agumento
 * @param space, de tipo Space
 * @return NO_ID en caso no encontrar espacio, en caso valido devuelve variable de tipo Id
 */
Id space_get_north(Space* space);

/*
 * @author Carlos Miret Fiuza
 * @brief Establece la coordenada sur pasada por argumento a un espacio pasado como argumento
 * @param space, de tipo Space y @param id de tipo Id
 * @return ERROR en caso no encontrar espacio o no id, en caso valido, devuelve OK
 */
STATUS space_set_south(Space* space, Id id);

/*
 * @author Miguel Ángel Liaño 
 * @brief Devuelve la coordenada sur de un espacio pasado como agumento
 * @param space, de tipo Space
 * @return NO_ID en caso no encontrar espacio, en caso valido devuelve variable de tipo Id
 */
Id space_get_south(Space* space);

/*
 * @author Carlos Miret Fiuza
 * @brief Establece la coordenada este pasada por argumento a un espacio pasado como argumento
 * @param space, de tipo Space y @param id de tipo Id
 * @return ERROR en caso no encontrar espacio o no id, en caso valido, devuelve OK
 */
STATUS space_set_east(Space* space, Id id);

/*
 * @author Miguel Ángel Liaño
 * @brief Devuelve la coordenada este de un espacio pasado como agumento
 * @param space, de tipo Space
 * @return NO_ID en caso no encontrar espacio, en caso valido devuelve variable de tipo Id
 */
Id space_get_east(Space* space);

/*
 * @author Carlos Miret Fiuza
 * @brief Establece la coordenada oeste pasada por argumento a un espacio pasado como argumento
 * @param space, de tipo Space y @param id de tipo Id
 * @return ERROR en caso no encontrar espacio o no id, en caso valido, devuelve OK
 */
STATUS space_set_west(Space* space, Id id);

/*
 * @author Miguel Ángel Liaño
 * @brief Devuelve la coordenada oeste de un espacio pasado como agumento
 * @param space, de tipo Space
 * @return NO_ID en caso no encontrar espacio, en caso valido devuelve variable de tipo Id
 */
Id space_get_west(Space* space);

/*
 * @author Carlos Miret Fiuza
 * @brief Devuelve el objeto de un espacio pasado como argumento
 * @param space, de tipo Space
 * @return FALSE en caso no no encontrar espacio y devuelve un objeto de la estructura espacio
 */
Set* space_get_objectsIds(Space* space);

/*
 * @author Miguel Ángel Liaño 
 * @brief Imprime los datos, del espacio pasado como argumento (nombre, dirección, norte, sur, si hay un objeto...)
 * @param space, de tipo Space
 * @return ERROR en caso no no encontrar espacio y devuelve OK en caso válido
 */
STATUS space_print(Space* space);

/*
 * @author Carlos Miret Fiuza
 * @brief Añade objetos en el espacio en función de su segundo argumento
 * @param space, Espacio. Espacio donde añadir el objeto
 * @param object, Object. Objeto a añadir en el juego
 * @return Ok si se añadieron los espacios correctamente o ERROR si no se pueden añadir las casillas
 */
STATUS space_add_object(Space* space, Id id); 

/* 
 * @author Miguel Ángel Liaño
 * @brief Devuelve los identificadores de objetos en un espacio dado por argumento
 * @param space, Espacio. Espacio donde se obtienen los ids
 * @return Ok si se añadieron los espacios correctamente o ERROR si no se pueden añadir las casillas
 */
/*
 * @author Carlos Miret Fiuza
 * @brief Comprueba si hay un objeto en un espacio dados por argumento
 * @param space, Espacio. Espacio donde comprobar si esta el objeto
 * @param object, Object. Objeto a comprobar
 * @return True si el objeto se encuentra en el espacio o False si no se encuentra
 */
BOOL space_is_object_id(Space *space, Id);

#endif
