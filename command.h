/* 
 * @file command.h
 * @author Miguel Ángel Liaño y Carlos Miret Fiuza
 * @version 1.0 
 * @date 10-02-2018 
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

/*Se definen los posibles comandos con los que puede interactuar el jugador */
typedef enum enum_Command {
  NO_CMD = -1, /*Comando erróneo*/
  UNKNOWN, /*Comando desconocido*/
  EXIT, /*Comando de salida*/
  FOLLOWING, /*Comando para avanzar*/
  PREVIOUS, /*Comando para retroceder*/
  GRASP,/*Comando para coger un objeto*/
  DROP,/*Comando para dejar un objeto*/
  RIGHT,/*Comando para avanzar a la siguiente casilla de oca*/
  LEFT,/*Comando para retroceder a la casilla anterior casilla de oca */
  ROLL/*Comando para lanzar el dado */
} T_Command;

/*
 * @author Miguel Ángel Liaño
 * @brief Interpreta el comando introducido por el usuario
 * @return Devuelve el comando introducido por el usuario
 */
T_Command get_user_input();

#endif

