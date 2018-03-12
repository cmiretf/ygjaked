#ifndef SET_H
#define SET_H
#include "types.h"
#include <stdio.h>
/*Número máximo disponible de identificadores*/
#define MAX_ID 100

/*Definición de la estructura Set contenedora de los Ids*/
typedef struct _Set Set;
/*
 * @author Miguel Ángel Liaño
 * @brief Inicializa set, (las direcciones y el numero de direcciones) 
 * @param id, de tipo Id (definida en types.h)
 * @return NULL en caso de error, y en caso válido, devuelve un puntero a Set
 */
Set *set_create();
/*
 * @author Miguel Ángel Liaño
 * @brief Borra un set pasado como argumento
 * @param Set, de tipo Set contenedora de un array de identificadores
 * @return ERROR en caso de error, y en caso válido, devuelve OK
 */
STATUS set_destroy(Set *set);
/*
 * @author Miguel Ángel Liaño
 * @brief Comprueba si un set pasado como argumento esta vacío
 * @param Set, de tipo Set contenedora de un array de identificadores
 * @return TRUE si está vacía, y FALSE  si no lo esta
 */
BOOL set_empty(Set* set);
/*
 * @author Miguel Ángel Liaño
 * @brief Copia una direccion de un set dado como argumento
 * @param Set, de tipo Set contenedora de un array de identificadores
 * @return ERROR en caso de error, y en caso válido al realizar la copia, devuelve OK
 */
STATUS id_copy(Id id);
/*
 * @author Miguel Ángel Liaño
 * @brief Compara una direccion dada como argumento en un set dado como argumento
 * @param Set, de tipo Set contenedora de un array de identificadores, id identificador
 * @return -1 si el identificador no se encuentra repetido, en caso contrario la posición donde está repetido en el set
 */
BOOL set_comparaId(Set *set,Id id);
/*
 * @author Miguel Ángel Liaño
 * @brief Añade una direccion dada como argumento en un set dado como argumento
 * @param Set, de tipo Set contenedora de un array de identificadores, id identificador
 * @return ERROR en caso de error, y en caso válido, devuelve OK
 */
STATUS set_anadir(Set *set, Id id);
/*
 * @author Miguel Ángel Liaño
 * @brief Elimina una direccion dada como argumento en un set dado como argumento
 * @param Set, de tipo Set contenedora de un array de identificadores, id identificador
 * @return ERROR en caso de error, y en caso válido, devuelve OK
 */
STATUS set_eliminar(Set *set, Id id);
/*
 * @author Miguel Ángel Liaño
 * @brief Devuelve los identificadores que almacena un set dado por argumento
 * @param Set, de tipo Set contenedora de un array de identificadores, id identificador
 * @return NO_ID en caso de error, y en caso válido, devuelve los identificadores
 */
Id set_get_Ids(Set *set);
/*
 * @author Miguel Ángel Liaño
 * @brief Imprime por pantalla las direcciones y numero de direcciones contenidas en set
 * @param Set, de tipo Set contenedora de un array de identificadores
 * @return ERROR en caso de error, y en caso válido, devuelve OK
 */
STATUS set_print(FILE *file,Set *set);

#endif
