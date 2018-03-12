#include <stdlib.h>
#include <stdio.h>
#include "set.h"
/*
 * @author Miguel Ángel Liaño
 * @brief Main para probar el funcionamiento del modulo set
 */
int main(int argc, char *argv[]){
  Set *set;
  Id id1=5;
  Id id2=7;
 
  set=set_create();

  set_anadir(set,id1);
  set_anadir(set,id2);
  set_eliminar(set,6);
  set_anadir(set,5);
  set_eliminar(set,id2);
  set_anadir(set,id2);
  set_anadir(set,8);
  set_print(stdout,set);

  set_destroy(set);
  return 0;
}
