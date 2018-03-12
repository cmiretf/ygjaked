/** 
 * @file game.h
 * @author Miguel Ángel Liaño y Carlos Miret Fiuza
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "object.h"
#include "command.h"
#include "space.h"
#include "die.h"
#include "types.h"

/*Se definen las distintas características del juego*/
typedef struct _Game{
  Player *player; /*Puntero a player*/
  Object *objects[MAX_OBJECTS + 1]; /*Array de punteros a object*/
  Space *spaces[MAX_SPACES + 1]; /*Espacios del juego*/
  T_Command last_cmd; /*Último comando introducido en el juego*/
  Die *dado;/*Dado a utilizar en el juego*/
}Game;

/*
 * @author Miguel Ángel Liaño
 * @brief Añade espacios en el juego en función de su segundo argumento
 * @param game, Juego. Juego donde añadir espacios
 * @param space, Space. Espacios a añadir en el juego
 * @return Ok si se añadieron los espacios correctamente o ERROR si no se pueden añadir las casillas
 */
STATUS game_add_space(Game* game, Space* space);

/*
 * @author Miguel Ángel Liaño 
 * @brief Añade objetos en el juego en función de su segundo argumento
 * @param game, Juego. Juego donde añadir objetos
 * @param space, Space. Espacios a añadir en el juego
 * @return Ok si se añadieron los objetos correctamente o ERROR si no se pueden añadir los objetos
 */
STATUS game_add_object(Game* game,Object* object);

/*
 * @author Miguel Ángel Liaño 
 * @brief Creación del juego e inicializa la localizacion del jugador y objeto además de cada "espacio" del mapa
 * @param game, Juego. Juego a crear
 * @return Error si no se puede crear alguno de los espacios del mapa. Ok si se crea el juego correctamente
 */
STATUS game_create(Game* game); 

/*
 * @author Carlos Miret Fiuza
 * @brief Creación del juego a partir de un archivo
 * @param game, Juego. Juego a crear
 * @param filename, Nombre de Archivo. Archivo contenedor de espacios del juego
 * @return Error si no se puede crear el juego o cargar los espacios. Ok si se crea el juego correctamente
 */
STATUS game_create_from_file(Game* game, char* filename); 

/*
 * @brief Comprueba que los comandos se actualizan en el juego correctamente
 * @param game, Juego donde se realiza el comando
 * @param T_command, Último comando introducido en el juego  
 * @return Ok si se implementa el último comando correctamente 
 */
STATUS game_update(Game* game, T_Command cmd);

/*
 * @author Carlos Miret Fiuza
 * @brief Elimina el juego, liberando memoria de cada elemento previamente creado (jugador, objeto, comandos, espacios del mapa...) pasado como argumento
 * @param game, Juego. Juego a borrar
 * @return Ok si se borra el juego correctamente
 */
STATUS game_destroy(Game* game);

/*
 * @author Carlos Miret Fiuza
 * @brief Comprueba si el juego ha finalizado
 * @param game, Juego de donde se obtienen los datos a imprimir
 * @return True si el juego ha finalizado, FALSE si continúa
 */
BOOL game_is_over(Game* game); 

/*
 * @author Carlos Miret Fiuza
 * @brief Imprime la pantalla del juego
 * @param game, Juego de donde se obtienen la pantalla a imprimir
 */
void game_print_screen(Game* game);

/*
 * @author Miguel Ángel Liaño
 * @brief Imprime los datos del juego (localización de objeto, jugador...)
 * @param game, Juego de donde se obtienen los datos a imprimir
 */
void game_print_data(Game* game); 

/*
 * @author Carlos Miret Fiuza
 * @brief Obtiene un espacio del juego
 * @param game, Juego. Juego donde obtener el espacio
 * @param id. Dirección de un espacio
 * @return Un espacio dada su dirección y NULL si la dirección dada es errónea
 */
Space* game_get_space(Game* game, Id id); 
/*
 * @author Miguel Ángel Liaño 
 * @brief Obtiene un objeto del juego
 * @param game, Juego. Juego donde obtener el objeto
 * @param id. Dirección del objeto
 * @return Un objeto dada su dirección y NULL si la dirección dada es errónea
 */
Object* game_get_object(Game* game, Id id);
/*
 * @author Carlos Miret Fiuza
 * @brief Obtiene la posición del jugador
 * @param game, Juego donde esta localizado el jugador
 * @return La dirección del jugador
 */
Id game_get_player_location(Game* game);

/*
 * @author Miguel Ángel Liaño
 * @brief Obtiene la posición del objeto
 * @param game, Juego donde esta localizado el objeto
 * @return La dirección del objeto
 */
Id game_get_object_location(Game* game, Object *object); 

/*
 * @author Carlos Miret Fiuza
 * @brief Obtiene el último comando utilizado en el juego
 * @param game, Juego de donde se obtiene el comando  
 * @return Último comando del juego
 */
T_Command game_get_last_command(Game* game); 


#endif
