#include "die.h"
/*
 * @author Carlos Miret Fiuza
 * @brief Main para probar el funcionamiento del dado
 */
int main(){
  Die *die;
  die=die_create();
  die_roll(die);
  die_print(stdout,die);
  die_destroy(die);
  

  return 0;
}
