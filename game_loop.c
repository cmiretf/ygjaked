/** 
 * @brief Define el bucle principal del juego
 * @file game_loop.c
 * @author Miguel Ángel Liaño y Carlos Miret Fiuza
 * @version 1.0 
 * @date 10-01-2015 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphic_engine.h"

int main(int argc, char *argv[]){

	Game game;
  	T_Command command = NO_CMD;
  	Graphic_engine *gengine;


  	if ( argc < 2 ){ /*Evalúa el número de argumentos recibidos, devolviendo Error si recibe menos de dos argumentos*/
		fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
		return 1;
	}

	if ( game_create_from_file(&game, argv[1]) == ERROR ){ /*Imprimirá un error si el juego no se ha podido crear a partir de un archivo pasado como argumento*/
	  	fprintf(stderr, "Error while initializing game.\n");
		return 1;
	}

	if ( (gengine = graphic_engine_create()) == NULL ){ /*Comprueba si se ha podido crear el motor gráfico del juego (interfaz), imprimiendo un error en caso negativo */
		fprintf(stderr, "Error while initializing graphic engine.\n");
		game_destroy(&game);
		return 1;
	}

	while ( (command != EXIT) && !game_is_over(&game) ){ /* Evolución del juego mientras que éste no se finalize, bien por comando o bien por el final del juego*/
		graphic_engine_paint_game(gengine, &game);
		command = get_user_input();
		game_update(&game, command);
	}

	game_destroy(&game);

	graphic_engine_destroy(gengine);

	return 0;

}
