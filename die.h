#ifndef DIE_H
#define DIE_H
#include "stdio.h"
#include "stdlib.h"
#include "types.h"
#include "time.h"

typedef struct _Die Die;

/*
 * @author Carlos Miret Fiuza
 * @brief Inicializa die, (la direccion y el numero del dado) 
 * @param id, de tipo Id (definida en types.h)
 * @return NULL en caso de error, y en caso válido, devuelve un puntero a Die
 */
Die* die_create();


/*
 * @author Carlos Miret Fiuza
 * @brief Borra un dado pasado como argumento
 * @param die, de tipo Die (definida en die.h, e implementada en este archivo)
 * @return ERROR en caso de error, y en caso válido, devuelve OK
 */
STATUS die_destroy(Die* die);

/*
 * @author Carlos Miret Fiuza
 * @brief Genera un numero aleatorio del 1 al 6
 * @param die, de tipo Die (definida en die.h, e implementada en este archivo)
 * @return -1 en caso de error, y en caso válido, devuelve el valor de la tirada de la estructura Die
 */
int die_roll(Die *die);

/*
 * @author Carlos Miret Fiuza
 * @brief Devuelve la ultima tirada del dado
 * @param die, de tipo Die (definida en die.h, e implementada en este archivo)
 * @return -1 en caso de error, y en caso válido, devuelve el valor de la tirada de la estructura Die
 */
int die_get_tirada(Die *die);
/*
 * @author Carlos Miret Fiuza
 * @brief Imprime por pantalla la direccion y numero del dado obtenido
 * @param Die, de tipo die
 * @return ERROR en caso de error, y en caso válido, devuelve OK
 */
int die_print(char *file, Die *die);

#endif
