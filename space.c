/**
 * @brief La tarea principal es definir la existencia o no de un objeto en el mapa y las direcciones del mismo
 *
 * @file space.c
 * @author Miguel Ángel Liaño y Carlos Miret Fiuza
 * @version 1.0
 * @date 10-2-2018
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"

/*Se definen las distintas características que puede poseer un espacio en el juego*/
struct _Space {
  Id id; /*Dirección de un espacio*/
  char name[WORD_SIZE + 1]; /*Nombre del espacio*/
  Id north; /*Dirección norte del espacio*/
  Id south; /*Dirección sur del espacio*/
  Id east; /*Dirección este del espacio*/
  Id west; /*Dirección west del espacio*/
  Set *objects; /*Direccion del objeto a partir de un espacio*/
  char *gdesc[MAX_GDESC][TAM_GDESC]; /*Array contenedor de las descripciones graficas (Oca, puente o muerte)*/
};

/*
 * @author Miguel Ángel Liaño 
 * @brief Inicializa un espacio dado un Id pasado como parametro
 * @param id, de tipo Id (definida en types.h)
 * @return NULL en caso de error, y en caso válido, devuelve un puntero a Space
 */
Space* space_create(Id id) {
  int i;

  Space *newSpace = NULL;

  if (id == NO_ID)
    return NULL;

  newSpace = (Space *) malloc(sizeof (Space));

  if (newSpace == NULL) {
    return NULL;
  }
  newSpace->id = id;

  newSpace->name[0] = '\0';

  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  
  newSpace->objects = set_create();
  if(newSpace->objects == NULL)
    return NULL;

  for(i=0;i<MAX_GDESC;i++)
    newSpace->gdesc[i][0] = '\0';

  return newSpace;
}

/*
 * @author Carlos Miret Fiuza
 * @brief Borra un espacio pasado como argumento
 * @param space, de tipo Space (definida en space.h, e implementada en este archivo)
 * @return ERROR en caso de error, y en caso válido, devuelve OK
 */
STATUS space_destroy(Space* space) {
  int i;

  if (!space) {
    return ERROR;
  }

  for(i=0;i<MAX_GDESC;i++)
    free(space->gdesc[i][0]);

  set_destroy(space->objects);

  free(space);
  space = NULL;

  return OK;
}
/*
 * @author Miguel Ángel Liaño 
 * @brief Establece las distintas descripciones gráficas para los espacios del juego
 * @param space, de tipo Space y @param char (haciendo alusion al nombre)
 * @return ERROR si el espacio dado es incorrecto o si no se detecta la palabra claves gdesc, y en caso válido, devuelve OK
 */
STATUS space_set_gdesc(Space *space, char *gdesc){

  if(!space)
    return ERROR;
  
  if(strcmp(gdesc,"oca")==0){
    space->gdesc[0][MAX_GDESC] = "       ";
    space->gdesc[1][MAX_GDESC] = "<O)__//";
    space->gdesc[2][MAX_GDESC] = " \\_-//";
    return OK;
   }
  else if(strcmp(gdesc,"puente")==0){
    space->gdesc[0][MAX_GDESC] = "  ___  ";
    space->gdesc[1][MAX_GDESC] = " // \\ ";
    space->gdesc[2][MAX_GDESC] = "//   \\";
    return OK;
  }
  else if(strcmp(gdesc,"muerte")==0){
    space->gdesc[0][MAX_GDESC] = "  ___  ";
    space->gdesc[1][MAX_GDESC] = " (O O) ";
    space->gdesc[2][MAX_GDESC] = " \\m// ";
    return OK;
  }
  else
    return ERROR;
}
/*
 * @author Miguel Ángel Liaño 
 * @brief Establece el nombre pasado por argumento a un espacio pasado por argumentos
 * @param space, de tipo Space y @param char (haciendo alusion al nombre)
 * @return ERROR en caso de ser el mismo nombre(el de la estructura space,
 *    y el pasado como parametro), y en caso válido, devuelve OK
 */
STATUS space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }

  return OK;
}

/*
 * @author Carlos Miret Fiuza
 * @brief Establece la coordenada norte pasada por argumento a un espacio pasado como argumento
 * @param space, de tipo Space y @param id de tipo Id
 * @return ERROR en caso no encontrar espacio o no id, en caso valido, devuelve OK
 */
STATUS space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}

/*
 * @author Miguel Ángel Liaño 
 * @brief Establece la coordenada sur pasada por argumento a un espacio pasado como argumento
 * @param space, de tipo Space y @param id de tipo Id
 * @return ERROR en caso no encontrar espacio o no id, en caso valido, devuelve OK
 */
STATUS space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}


/*
 * @author Carlos Miret Fiuza
 * @brief Establece la coordenada este pasada por argumento a un espacio pasado como argumento
 * @param space, de tipo Space y @param id de tipo Id
 * @return ERROR en caso no encontrar espacio o no id, en caso valido, devuelve OK
 */
STATUS space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}


/*
 * @author Miguel Ángel Liaño 
 * @brief Establece la coordenada oeste pasada por argumento a un espacio pasado como argumento
 * @param space, de tipo Space y @param id de tipo Id
 * @return ERROR en caso no encontrar espacio o no id, en caso valido, devuelve OK
 */
STATUS space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}

/*
 * @author Carlos Miret Fiuza
 * @brief Devuelve el nombre de un espacio pasado como argumento
 * @param space, de tipo Space
 * @return NULL en caso no encontrar espacio, en caso valido devuelve char
 */
const char * space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}
/*
 * @author Miguel Ángel Liaño 
 * @brief Devuelve la dirección de un espacio pasado como agumento
 * @param space, de tipo Space
 * @return NO_ID en caso no encontrar espacio, en caso valido devuelve variable de tipo Id
 */
Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

/*
 * @author Carlos Miret Fiuza
 * @brief Devuelve la coordenada norte de un espacio pasado como agumento
 * @param space, de tipo Space
 * @return NO_ID en caso no encontrar espacio, en caso valido devuelve variable de tipo Id
 */
Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}


/*
 * @author Miguel Ángel Liaño
 * @brief Devuelve la coordenada sur de un espacio pasado como agumento
 * @param space, de tipo Space
 * @return NO_ID en caso no encontrar espacio, en caso valido devuelve variable de tipo Id
 */
Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

/*
 * @author Carlos Miret Fiuza
 * @brief Devuelve la coordenada este de un espacio pasado como agumento
 * @param space, de tipo Space
 * @return NO_ID en caso no encontrar espacio, en caso valido devuelve variable de tipo Id
 */
Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

/*
 * @author Miguel Ángel Liaño 
 * @brief Devuelve la coordenada oeste de un espacio pasado como agumento
 * @param space, de tipo Space
 * @return NO_ID en caso no encontrar espacio, en caso valido devuelve variable de tipo Id
 */
Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}
/*
 * @author Carlos Miret Fiuza
 * @brief Devuelve el objeto de un espacio pasado como argumento
 * @param space, de tipo Space
 * @return FALSE en caso no no encontrar espacio y devuelve un objeto de la estructura espacio
 */
Set* space_get_objectsIds(Space* space) {
  if (!space || space->objects == NULL) {
    return FALSE;
  }

  if(set_empty(space->objects) == TRUE)
    return NULL;
  return space->objects;
}

/*
 * @author Miguel Ángel Liaño
 * @brief Imprime los datos, del espacio pasado como argumento (nombre, dirección, norte, sur, si hay un objeto...)
 * @param space, de tipo Space
 * @return ERROR en caso no no encontrar espacio y devuelve OK en caso válido
 */
STATUS space_print(Space* space) {
  Id idaux = NO_ID;

  if (!space) {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  idaux = space_get_north(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }

  idaux = space_get_south(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }

  idaux = space_get_east(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }

  idaux = space_get_west(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  if (space_get_objectsIds(space)) {
    fprintf(stdout, "---> Object in the space.\n");
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}

/* 
 * @author Carlos Miret Fiuza
 * @brief Añade objetos en el espacio en función de su segundo argumento
 * @param space, Espacio. Espacio donde añadir el objeto
 * @param object, Object. Objeto a añadir en el juego
 * @return Ok si se añadieron los espacios correctamente o ERROR si no se pueden añadir las casillas
 */
STATUS space_add_object(Space* space, Id id){

  int i = 0;

  if( space==NULL || id==NO_ID ) return ERROR;

  while ( (i < MAX_ID) && (set_comparaId(space->objects,NO_ID) != TRUE)){
    i++;
  }

  if (i >= MAX_ID) {
    return ERROR;
  }

  set_anadir(space->objects, id);
  
  return TRUE;
} 

/* 
 * @author Miguel Ángel Liaño
 * @brief Comprueba si hay un objeto en un espacio dados por argumento
 * @param space, Espacio. Espacio donde comprobar si esta el objeto
 * @param object, Object. Objeto a comprobar
 * @return True si el objeto se encuentra en el espacio o False si no se encuentra
 */
BOOL space_is_object_id(Space *space, Id id){

  if(space == NULL) 
    return FALSE;
  
  if(set_comparaId(space->objects,id)==TRUE)
    return TRUE;
  
  return FALSE;
}
