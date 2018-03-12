/** 
 * @file object.h
 * @author Carlos Miret Fiuza
 * @version 1.0 
 * @date 10-2-2018 
 * @copyright GNU Public License
 */
#ifndef OBJETO_H
#define OBJETO_H
#include "types.h"

/*Tamaño máximo para el nombre de un objeto*/
#define MAX_NOMBRE 20
#define MAX_OBJECTS 4

typedef struct _Object Object;

/*
 * @author Carlos Miret Fiuza
 * @brief Inicializa un objeto pasado como parametro
 * @param id, de tipo Id (definida en types.h)
 * @return NULL en caso de error, y en caso válido, devuelve un puntero a Object
 */
Object* object_create(Id id, Id id_location);

/*
 * @author Carlos Miret Fiuza
 * @brief Borra un objeto pasado como argumento
 * @param objeto de tipo Objeto
 * @return ERROR en caso de no encontrar objeto, y en caso válido OK
 */
STATUS object_destroy(Object* object);

/*
 * @author Carlos Miret Fiuza
 * @brief Devuelve la dirección de un espacio pasado como agumento
 * @param objeto, de tipo Objeto
 * @return NO_ID en caso no encontrar objeto, en caso valido devuelve variable de tipo Id
 */
Id object_get_id(Object* object);

/*
 * @author Carlos Miret Fiuza
 * @brief Borra un objeto pasado como argumento
 * @param objeto de tipo Objeto
 * @return ERROR en caso de no encontrar objeto, y en caso válido OK
 */
STATUS object_set_name(Object* object, char* name);

/*
 * @author Carlos Miret Fiuza
 * @brief Devuelve el nombre de un objeto pasado como argumento
 * @param objeto, de tipo Objeto
 * @return NULL en caso no encontrar objeto, en caso valido devuelve char
 */
const char* object_get_name(Object* object);
/*
 * @author Carlos Miret Fiuza
 * @brief Establece la posicion de un objeto en un espacio
 * @param objeto, de tipo Objeto
 * @return ERROR en caso no encontrar objeto, en caso valido devuelve ok
 */
STATUS object_set_location(Object *object,Id id);
/*
 * @author Carlos Miret Fiuza
 * @brief Devuelve la posicion de un objeto en un espacio
 * @param objeto, de tipo Objeto
 * @return NO_ID en caso no encontrar objeto, en caso valido la direccion del objeto
 */
Id object_get_location(Object *object);
/*
 * @author Carlos Miret Fiuza
 * @brief Imprime los datos, del objeto pasado como argumento (nombre, dirección, norte, sur, si hay un objeto...)
 * @param objeto, de tipo Objeto
 * @return ERROR en caso no no encontrar objeto y devuelve OK en caso válido
 */
STATUS object_print(Object* object);

/*
 * @author Carlos Miret Fiuza
 * @brief Establece la dirección de un objeto pasado como agumento a partir de la direccion dada como argumento
 * @param objeto, de tipo Objeto
 * @return NO_ID en caso no encontrar objeto, en caso valido devuelve variable de tipo Id
 */
STATUS object_set_id(Object* object, Id id);


#endif
