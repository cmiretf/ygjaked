/** 
 * @brief Especificación del tipo de objeto y su localización
 * 
 * @file object.c
 * @author Carlos Miret Fiuza
 * @version 1.0 
 * @date 10-2-2018 
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
struct _Object{
    Id id;
    char nombre[MAX_NOMBRE];
    Id object_location;
};
/*
 * @author Carlos Miret Fiuza
 * @brief Inicializa un objeto pasado como parametro
 * @param id, de tipo Id (definida en types.h)
 * @return NULL en caso de error, y en caso válido, devuelve un puntero a Object
 */
Object* object_create(Id id, Id id_location) {

  Object *newObject = NULL;
  int i;

  if (id == NO_ID)
    return NULL;

  newObject = (Object *) malloc(sizeof (Object));

  if (newObject == NULL) {
    return NULL;
  }
  newObject->id = id;
  for(i=0;i<MAX_NOMBRE;i++)
    newObject->nombre[i] ='\0';

  newObject->object_location = id_location;

  return newObject;
}

/*
 * @author Carlos Miret Fiuza
 * @brief Borra un objeto pasado como argumento
 * @param objeto de tipo Objeto
 * @return ERROR en caso de no encontrar objeto, y en caso válido OK
 */
STATUS object_destroy(Object* object) {
  if (!object) {
    return ERROR;
  }

  free(object);
  object = NULL;

  return OK;
}

/*
 * @author Carlos Miret Fiuza
 * @brief Establece el nombre pasado por argumento a un objeto pasado por argumentos
 * @param objeto de tipo Objeto y @param name de tipo char
 * @return ERROR en caso de no encontrar objeto, no encontrar el nombre o que sea el mismo al pasado como parametro, y en caso válido OK
 */
STATUS object_set_name(Object* object, char* name) {
  if (!object || !name) {
    return ERROR;
  }

  if (!strcpy(object->nombre, name)) {
    return ERROR;
  }

  return OK;
}

/*
 * @author Carlos Miret Fiuza
 * @brief Devuelve el nombre de un objeto pasado como argumento
 * @param objeto, de tipo Objeto
 * @return NULL en caso no encontrar objeto, en caso valido devuelve char
 */
const char * object_get_name(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->nombre;
}

/*
 * @author Carlos Miret Fiuza
 * @brief Devuelve la dirección de un objeto pasado como agumento
 * @param objeto, de tipo Objeto
 * @return NO_ID en caso no encontrar objeto, en caso valido devuelve variable de tipo Id
 */
Id object_get_id(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->id;
}
/*
 * @author Carlos Miret Fiuza
 * @brief Establece la dirección de un objeto pasado como agumento a partir de la direccion dada como argumento
 * @param objeto, de tipo Objeto
 * @return NO_ID en caso no encontrar objeto, en caso valido devuelve variable de tipo Id
 */
STATUS object_set_id(Object* object, Id id) {
  if (!object) {
    return ERROR;
  }
  object->id=id;
  return ERROR;
}

Id object_get_location(Object *object){
  if(object == NULL)
    return NO_ID;
  
  return object->object_location;
}

STATUS object_set_location(Object *object,Id id){
  if(object == NULL)
    return ERROR;
  
  object->object_location = id;
  return OK;
}
/*
 * @author Carlos Miret Fiuza
 * @brief Imprime los datos, del objeto pasado como argumento (nombre, dirección, norte, sur, si hay un objeto...)
 * @param objeto, de tipo Objeto
 * @return ERROR en caso no no encontrar objeto y devuelve OK en caso válido
 */
STATUS object_print(Object* object) {

  if (!object) {
    return ERROR;
  }

  fprintf(stdout, "--> Objeto (Id: %ld; Name: %s; Location: %ld)\n", object->id, object->nombre, object->object_location);


  return OK;
}



