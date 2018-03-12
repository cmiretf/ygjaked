/* 
 * @file game_reader.h
 * @author Miguel Ángel Liaño y Carlos Miret Fiuza
 * @version 1.0 
 * @date 10-02-2018 
 * @copyright GNU Public License
 */
#ifndef GAME_READER
#define GAME_READER
#include "game.h"
#include "types.h"

/*
 * @author Miguel Ángel Liaño
 * @brief Carga los espacios del juego
 * @param game, Juego donde se añadirán los espacios
 * @param filename, Archivo con el contenido de los espacios 
 * @return Error si algunos de los argumentos son erróneos y OK si se consigue realizar correctamente la carga de los espacios
 */
STATUS gameReader_load_spaces(Game* game, char* filename);

/*
 * @author Carlos Miret Fiuza
 * @brief Carga los objeto del juego
 * @param game, Juego donde se añadirán los objetos
 * @param filename, Archivo con el contenido de los espacios 
 * @return Error si algunos de los argumentos son erróneos y OK si se consigue realizar correctamente la carga de los objetos
 */
STATUS gameReader_load_objects(Game* game, char* filename);
#endif  
