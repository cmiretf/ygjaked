#include "set.h"
#include <stdlib.h>
#include <stdio.h>

/*Definición de la estructura Set contenedora de los Ids*/
struct _Set{
	Id id[MAX_ID];
	int nIds;
};

/*
 * @author Miguel Ángel Liaño
 * @brief Inicializa set, (las direcciones y el numero de direcciones) 
 * @param id, de tipo Id (definida en types.h)
 * @return NULL en caso de error, y en caso válido, devuelve un puntero a Set
 */
Set *set_create(){
  int i=0;
  Set *set = NULL;

  set=(Set *)malloc(sizeof (Set));

  if (set == NULL)
    return NULL;
  
  for(i=0;i<MAX_ID;i++)
     set->id[i]=NO_ID;

  set->nIds=0;
  
  return set;

}

/*
 * @author Miguel Ángel Liaño
 * @brief Borra un set pasado como argumento
 * @param Set, de tipo Set contenedora de un array de identificadores
 * @return ERROR en caso de error, y en caso válido, devuelve OK
 */
STATUS set_destroy(Set *set){
  if (set==NULL)
    return ERROR;

  free(set);
  set=NULL;

  return OK;
}
/*
 * @author Miguel Ángel Liaño
 * @brief Comprueba si un set pasado como argumento esta vacío
 * @param Set, de tipo Set contenedora de un array de identificadores
 * @return TRUE si está vacía, y FALSE  si no lo esta
 */
BOOL set_empty(Set* set){
  if(set == NULL)
    return TRUE;

  if(set->nIds == 0)
    return TRUE;

  return FALSE;
}
/*
 * @author Miguel Ángel Liaño
 * @brief Copia una direccion de un set dado como argumento
 * @param Set, de tipo Set contenedora de un array de identificadores
 * @return ERROR en caso de error, y en caso válido al realizar la copia, devuelve OK
 */
STATUS id_copy(Id id){
   Id aux=NO_ID;
   aux=id;
   return aux;
}

/*
 * @author Miguel Ángel Liaño
 * @brief Compara una direccion dada como argumento en un set dado como argumento
 * @param Set, de tipo Set contenedora de un array de identificadores, id identificador
 * @return -1 si el identificador no se encuentra repetido, en caso contrario la posición donde está repetido en el set
 */
BOOL set_comparaId(Set *set,Id id){
  int i=0;
  for(i=0;i<set->nIds;i++){
    if(set->id[i]==id)
      return TRUE;
  }

  return FALSE;
}

/*
 * @author Miguel Ángel Liaño
 * @brief Añade una direccion dada como argumento en un set dado como argumento
 * @param Set, de tipo Set contenedora de un array de identificadores, id identificador
 * @return ERROR en caso de error, y en caso válido, devuelve OK
 */
STATUS set_anadir(Set *set, Id id){
  Id aux=NO_ID;
  int i;
  if(set==NULL && set->nIds>MAX_ID-1) return ERROR;

  if(set_comparaId(set,id)==FALSE){
    for(i=0;i<MAX_ID;i++){
      if(set->id[i]==NO_ID){
        aux=id_copy(id);
        set->id[i]=aux;
        set->nIds++;
        break;
      }
    }
  }
  return OK;
}
/*
 * @author Miguel Ángel Liaño
 * @brief Elimina una direccion dada como argumento en un set dado como argumento
 * @param Set, de tipo Set contenedora de un array de identificadores, id identificador
 * @return ERROR en caso de error, y en caso válido, devuelve OK
 */
STATUS set_eliminar(Set *set, Id id){
  int i;

  if(set==NULL||set->nIds==0)return ERROR;

  if(set_comparaId(set,id)==TRUE){
    for(i=0;i<MAX_ID;i++){
      if(set->id[i]==id){
        set->id[i]=NO_ID;
        set->nIds--;
      }
    }
  }
  return OK;
}

/*
 * @author Miguel Ángel Liaño
 * @brief Imprime por pantalla las direcciones y numero de direcciones contenidas en set
 * @param Set, de tipo Set contenedora de un array de identificadores
 * @return ERROR en caso de error, y en caso válido, devuelve OK
 */
STATUS set_print(FILE *file,Set *set){
  int i=0;
  if(set==NULL) return ERROR;
  fprintf(file,"Numero de direcciones=%d \n",set->nIds);
  for(i=0;i<set->nIds;i++)
	fprintf(file,"Dirección %d: %ld \n",i+1,set->id[i]);
  
  return OK;
	
}

