#include "die.h"

struct _Die{
   Id id;
   int tirada;	
};

/*
 * @author Carlos Miret Fiuza
 * @brief Inicializa die, (la direccion y el numero del dado) 
 * @param id, de tipo Id (definida en types.h)
 * @return NULL en caso de error, y en caso válido, devuelve un puntero a Die
 */
Die* die_create() {

  Die *die = NULL;

  die = (Die *) malloc(sizeof (Die));

  if (die == NULL) {
    return NULL;
  }
  die->id = NO_ID;
  die->tirada=0;

  return die;
}


/*
 * @author Carlos Miret Fiuza
 * @brief Borra un dado pasado como argumento
 * @param die, de tipo Die (definida en die.h, e implementada en este archivo)
 * @return ERROR en caso de error, y en caso válido, devuelve OK
 */
STATUS die_destroy(Die* die) {
  if (!die) {
    return ERROR;
  }

  free(die);
  die = NULL;

  return OK;
}

/*
 * @author Carlos Miret Fiuza
 * @brief Genera un numero aleatorio del 1 al 6
 * @param die, de tipo Die (definida en die.h, e implementada en este archivo)
 * @return -1 en caso de error, y en caso válido, devuelve el valor de la tirada de la estructura Die
 */
int die_roll(Die *die){
  if(die==NULL)return -1;
  srand(time(NULL));
  die->tirada=1 + rand()%((6+1)-1);
  return die->tirada;
}
/*
 * @author Carlos Miret Fiuza
 * @brief Devuelve la ultima tirada del dado
 * @param die, de tipo Die (definida en die.h, e implementada en este archivo)
 * @return -1 en caso de error, y en caso válido, devuelve el valor de la tirada de la estructura Die
 */
int die_get_tirada(Die *die){
  if(die == NULL)return -1;
  return die->tirada;
}

/*
 * @author Carlos Miret Fiuza
 * @brief Imprime por pantalla la direccion y numero del dado obtenido
 * @param Die, de tipo die
 * @return ERROR en caso de error, y en caso válido, devuelve OK
 */
int die_print(char *file, Die *die){
  if(die==NULL) return ERROR;
  return fprintf(stdout,"Id=%ld.\nNumero del dado: %d.\n",die->id, die->tirada);
}

