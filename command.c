/* 
 * @brief Implementa la lectura de comandos
 * @file command.c
 * @author Miguel Ángel Liaño y Carlos Miret Fiuza
 * @version 1.0 
 * @date 10-02-2018 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <strings.h>
#include "command.h"

#define CMD_LENGHT 30 /*Longitud maxima del nombre del comando*/
#define N_CMD 10 /*Representa el numero de comandos*/

char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Following", "Previous", "Grasp", "Drop", "Right", "Left", "Roll"}; /*Comandos extendidos*/
char *short_cmd_to_str[N_CMD] ={"","","e","f","p", "g", "d", "r", "l", "x"}; /*Comandos abreviados*/

 /*
 * @author Miguel Ángel Liaño
 * @brief Interpreta el comando introducido por el usuario
 * @return Devuelve el comando introducido por el usuario
 */

T_Command get_user_input(){
  T_Command cmd = NO_CMD;
  char input[CMD_LENGHT] = "";
  int i=UNKNOWN - NO_CMD + 1;
    if (scanf("%s", input) > 0){    
      cmd = UNKNOWN;
        while(cmd == UNKNOWN && i < N_CMD){
  	  if (!strcasecmp(input,short_cmd_to_str[i]) || !strcasecmp(input,cmd_to_str[i])){
            cmd = i + NO_CMD;
          }
           else{
	     i++;
           }
    }
    }
  return cmd;
}
