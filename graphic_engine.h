/** 
 * @file graphic_engine.h
 * @author Miguel Ángel Liaño y Carlos Miret Fiuza
 * @version 1.0 
 * @date 10-2-2018 
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"

typedef struct _Graphic_engine Graphic_engine;

/*
 * @author Carlos Miret Fiuza
 * @brief Crea y devuelve la interfaz de juego y la inicializa ( mapa, descripcion ...) 
 * @params void
 * @return puntero a Graphic_engine
 */
Graphic_engine* graphic_engine_create(); 

/*
 * @author Carlos Miret Fiuza
 * @brief Borra la interfaz de juego pasada por argumento
 * @params puntero a Graphic_engine
 * @return void
 */
void graphic_engine_destroy(Graphic_engine *ge); 

/*
 * @author Miguel Ángel Liaño
 * @brief Imprime en cada area del motor gráfico pasado como primer argumento, sus correspondientes datos del juego pasado como segundo argumento
 * @params puntero a Graphic_engine, y puntero a Game
 * @return void
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game); 

/*
 * @author Miguel Ángel Liaño 
 * @brief Imprime los comandos recibidos por argumento en la zona del motor gráfico dado por argumento
 * @params puntero a Graphic_engine, y puntero a char
 * @return void
 */
void graphic_engine_write_command(Graphic_engine *ge, char *str); 


#endif
