/** 
 * @brief Implementa la interfaz del juego y la interpretación de cada comando en el juego
 * @file game.c
 * @author Miguel Ángel Liaño y Carlos Miret Fiuza
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_reader.h"

/*Numero de devoluciones de los comandos, es 10 ya que uno de los comandos no devuelve nada*/
#define N_CALLBACK 10


/**
   Define the function type for the callbacks
*/
typedef void (*callback_fn)(Game* game);

/**
   List of callbacks for each command in the game 
*/

/*
 * @author Miguel Ángel Liaño
 * @brief Interpretación en el juego de un comando indefinido
 * @param game, Juego donde se interpreta el comando
 */
void game_callback_unknown(Game* game); 
/*
 * @author Carlos Miret Fiuza
 * @brief Interpretación en el juego del comando salida
 * @param game, Juego donde se interpreta el comando
 */
void game_callback_exit(Game* game);
/*
 * @author Miguel Ángel Liaño 
 * @brief Interpretación en el juego del comando de avance
 * @param game, Juego donde se interpreta el comando
 */
void game_callback_following(Game* game);
/*
 * @author Carlos Miret Fiuza
 * @brief Interpretación en el juego del comando de retroceder
 * @param game, Juego donde se interpreta el comando
 */
void game_callback_previous(Game* game);
/*
 * @author Miguel Ángel Liaño
 * @brief Interpretación en el juego del comando de coger
 * @param game, Juego donde se interpreta el comando
 */
void game_callback_grasp(Game* game);

/*
 * @author Carlos Miret Fiuza
 * @brief Interpretación en el juego del comando de soltar
 * @param game, Juego donde se interpreta el comando
 */
void game_callback_drop(Game* game);
/*
 * @author Miguel Ángel Liaño 
 * @brief Interpretación en el juego del comando de avanzar a la derecha si está en una oca
 * @param game, Juego donde se interpreta el comando
 */
void game_callback_right(Game* game);
/*
 * @author Miguel Ángel Liaño 
 * @brief Interpretación en el juego del comando de avanzar a la izquierda si está en una oca
 * @param game, Juego donde se interpreta el comando
 */
void game_callback_left(Game* game);
/*
 * @author Carlos Miret Fiuza 
 * @brief Interpretación en el juego para la tirada del dado
 * @param game, Juego donde se interpreta el comando
 */
void game_callback_rollDie(Game *game);

/*Se definen las distintas devoluciones en el juego de los comandos*/
static callback_fn game_callback_fn_list[N_CALLBACK]={
  game_callback_unknown,
  game_callback_exit,
  game_callback_following,
  game_callback_previous,
  game_callback_grasp,
  game_callback_drop,
  game_callback_right,
  game_callback_left,
  game_callback_rollDie
};

/*
 * @author Miguel Ángel Liaño
 * @brief Añade espacios en el juego en función de su segundo argumento
 * @param game, Juego. Juego donde añadir espacios
 * @param space, Space. Espacios a añadir en el juego
 * @return Ok si se añadieron los espacios correctamente o ERROR si no se pueden añadir las casillas
 */
STATUS game_add_space(Game* game, Space* space); 

/**
   Private functions
*/

/*
 * @author Carlos Miret Fiuza
 * @brief Dirección de una casilla del juego
 * @param game, Juego. Juego donde obtener la direccion de casilla
 * @param position. Posición concreta de un espacio
 * @return La dirección del espacio si todo es correcto, o -1 si los argumentos son incorrectos
 */
Id game_get_space_id_at(Game* game, int position);

/*
 * @author Carlos Miret Fiuza
 * @brief Establece la posición del jugador en el juego
 * @param game, Juego donde esta localizado el jugador
 * @param id. Dirección donde establecer el jugador
 * @return ERROR si la dirección dada es errónea
 */
STATUS game_set_player_location(Game* game, Id id);
 
/*
 * @author Carlos Miret Fiuza
 * @brief Establece la posición del objeto en el juego
 * @param game, Juego donde esta localizado el objeto
 * @param id. Dirección donde establecer el objeto
 * @return ERROR si la dirección dada es errónea
 */
STATUS game_set_object_location(Game* game, Id id_space, Object* object); 

/**
   Game interface implementation
*/

/*
 * @author Miguel Ángel Liaño 
 * @brief Creación del juego e inicializa la localizacion del jugador y objeto además de cada "espacio" del mapa
 * @param game, Juego. Juego a crear
 * @return Error si no se puede crear alguno de los espacios del mapa. Ok si se crea el juego correctamente
 */
STATUS game_create(Game* game) {
  int i;
  
  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }
  
  game->player = NULL;
  
  for(i = 0;i < MAX_OBJECTS; i++){
    game->objects[i] = NULL;
  }

  game->last_cmd = NO_CMD;
  
  return OK;
}
/*
 * @author Carlos Miret Fiuza
 * @brief Creación del juego a partir de un archivo
 * @param game, Juego. Juego a crear
 * @param filename, Nombre de Archivo. Archivo contenedor de espacios del juego
 * @return Error si no se puede crear el juego o cargar los espacios. Ok si se crea el juego correctamente
 */
STATUS game_create_from_file(Game* game, char* filename) {

  if (game_create(game) == ERROR)
    return ERROR;

  if (gameReader_load_spaces(game, filename) == ERROR)
    return ERROR;

  if (gameReader_load_objects(game, filename) == ERROR)
    return ERROR;

  game->player = player_create(0);
  game_set_player_location(game, game_get_space_id_at(game, 0));
  player_set_name(game->player, "O");

  return OK;
}

/*
 * @author Carlos Miret Fiuza
 * @brief Elimina el juego, liberando memoria de cada elemento previamente creado (jugador, objeto, comandos, espacios del mapa...) pasado como argumento
 * @param game, Juego. Juego a borrar
 * @return Ok si se borra el juego correctamente
 */
STATUS game_destroy(Game* game) {
  int i = 0;

  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
    space_destroy(game->spaces[i]);
  }

  for (i = 0; (i < MAX_OBJECTS) && (game->objects[i] != NULL); i++) {
    object_destroy(game->objects[i]);
  }

  player_destroy(game->player);
        
  return OK;
}

/*
 * @author Miguel Ángel Liaño
 * @brief Añade espacios en el juego en función de su segundo argumento
 * @param game, Juego. Juego donde añadir espacios
 * @param space, Space. Espacios a añadir en el juego
 * @return Ok si se añadieron los espacios correctamente o ERROR si no se pueden añadir las casillas
 */
STATUS game_add_space(Game* game, Space* space) {
  int i = 0;

  if (space == NULL) {
    return ERROR;
  }

  while ( (i < MAX_SPACES) && (game->spaces[i] != NULL)){
    i++;
  }

  if (i >= MAX_SPACES) {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}

/*
 * @author Miguel Ángel Liaño 
 * @brief Añade objetos en el juego en función de su segundo argumento
 * @param game, Juego. Juego donde añadir objetos
 * @param space, Space. Espacios a añadir en el juego
 * @return Ok si se añadieron los objetos correctamente o ERROR si no se pueden añadir los objetos
 */
STATUS game_add_object(Game* game, Object* object){
  int i = 0;

  if (object == NULL) {
    return ERROR;
  }

  while ( (i < MAX_OBJECTS) && (game->objects[i] != NULL)){
    i++;
  }

  if (i >= MAX_OBJECTS){
    return ERROR;
  }

  game->objects[i] = object;

  return OK;
}
/*
 * @author Carlos Miret Fiuza
 * @brief Dirección de una casilla del juego
 * @param game, Juego. Juego donde obtener la direccion de casilla
 * @param position. Posición concreta de un espacio
 * @return La dirección del espacio si todo es correcto, o -1 si los argumentos son incorrectos
 */
Id game_get_space_id_at(Game* game, int position) {

  if (position < 0 || position >= MAX_SPACES) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

/*
 * @author Carlos Miret Fiuza
 * @brief Obtiene un espacio del juego
 * @param game, Juego. Juego donde obtener el espacio
 * @param id. Dirección de un espacio
 * @return Un espacio dada su dirección y NULL si la dirección dada es errónea
 */
Space* game_get_space(Game* game, Id id){
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }
    
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    if (id == space_get_id(game->spaces[i])){
      return game->spaces[i];
    }
  }
    
  return NULL;
}
/*
 * @author Miguel Ángel Liaño 
 * @brief Obtiene un objeto del juego
 * @param game, Juego. Juego donde obtener el objeto
 * @param id. Dirección del objeto
 * @return Un objeto dada su dirección y NULL si la dirección dada es errónea
 */
Object* game_get_object(Game* game, Id id){
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }
    
  for (i = 0; i < MAX_SPACES && game->objects[i] != NULL; i++) {
    if (id == object_get_id(game->objects[i])){
      return game->objects[i];
    }
  }
    
  return NULL;
}
/*
 * @author Carlos Miret Fiuza
 * @brief Establece la posición del jugador en el juego
 * @param game, Juego donde esta localizado el jugador
 * @param id. Dirección donde establecer el jugador
 * @return ERROR si la dirección dada es errónea
 */
STATUS game_set_player_location(Game* game, Id id) {
    
  if (id == NO_ID) {
    return ERROR;
  }
	
  player_set_id(game->player,id);
	
  return OK;
}

/*
 * @author Miguel Ángel Liaño
 * @brief Establece la posición del objeto en el juego
 * @param game, Juego donde esta localizado el objeto
 * @param id. Id el objeto
 * @return ERROR si la dirección dada es errónea
 */
STATUS game_set_object_location(Game* game, Id id_space, Object* object) {
  int i;
  Id space_aux, object_aux;

  if (game == NULL || id_space == NO_ID || object == NULL ) {
    return ERROR;
  }
  for(i=0;i<MAX_SPACES && game->spaces[i]!=NULL;i++){
    space_aux=space_get_id(game->spaces[i]);
    if(space_aux == id_space)
      object_aux = object_get_id(object);
      object_set_location(object,id_space);
      space_add_object(game->spaces[i],object_aux);
   }
  return OK;
}

/*
 * @author Carlos Miret Fiuza
 * @brief Obtiene la posición del jugador
 * @param game, Juego donde esta localizado el jugador
 * @return La dirección del jugador
 */
Id game_get_player_location(Game* game) {
  return player_get_id(game->player);
}

/*
 * @author Miguel Ángel Liaño
 * @brief Obtiene la posición del objeto
 * @param game, Juego donde esta localizado el objeto
 * @return La dirección del objeto
 */
Id game_get_object_location(Game* game, Object* object) {

  if (game == NULL || object == NULL) {
    return NO_ID;
  }
  
  return object_get_location(object);
}

/*
 * @author Miguel Ángel Liaño
 * @brief Comprueba que los comandos se actualizan en el juego correctamente
 * @param game, Juego donde se realiza el comando
 * @param T_command, Último comando introducido en el juego  
 * @return Ok si se implementa el último comando correctamente 
 */
STATUS game_update(Game* game, T_Command cmd) {
  game->last_cmd = cmd;
  (*game_callback_fn_list[cmd])(game);
  return OK;
}

/*
 * @author Carlos Miret Fiuza
 * @brief Obtiene el último comando utilizado en el juego
 * @param game, Juego de donde se obtiene el comando  
 * @return Último comando del juego
 */
T_Command game_get_last_command(Game* game){
  return game->last_cmd;
}

/*
 * @author Miguel Ángel Liaño
 * @brief Imprime los datos del juego (localización de objeto, jugador...)
 * @param game, Juego de donde se obtienen los datos a imprimir
 */
void game_print_data(Game* game) {
  int i = 0;
  
  printf("\n\n-------------\n\n");
  
  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Objects: \n");
  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) {
    object_print(game->objects[i]);
  }

  /*printf("=> Object location: %d\n", (int) game_get_object_location(game,)); */   
  printf("=> Player location: %d\n", (int) player_get_id(game->player));
  printf("prompt:> ");
}

/*
 * @author Carlos Miret Fiuza
 * @brief Comprueba si el juego ha finalizado
 * @param game, Juego de donde se obtienen los datos a imprimir
 * @return True si el juego ha finalizado, FALSE si continúa
 */
BOOL game_is_over(Game* game) {
  return FALSE;
}

/**
   Callbacks implementation for each action 
*/

/*
 * @author Miguel Ángel Liaño 
 * @brief Interpretación en el juego de un comando indefinido
 * @param game, Juego donde se interpreta el comando
 */
void game_callback_unknown(Game* game) {
}

/*
 * @author Carlos Miret Fiuza
 * @brief Interpretación en el juego del comando salida
 * @param game, Juego donde se interpreta el comando
 */
void game_callback_exit(Game* game) {
}

/*
 * @author Miguel Ángel Liaño
 * @brief Interpretación en el juego del comando de avance
 * @param game, Juego donde se interpreta el comando
 */
void game_callback_following(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  
  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }
  
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

/*
 * @author Carlos Miret Fiuza
 * @brief Interpretación en el juego del comando de retroceder
 * @param game, Juego donde se interpreta el comando
 */
void game_callback_previous(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  
  space_id = game_get_player_location(game);
  
  if (NO_ID == space_id) {
    return;
  }
  
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
      }
      return;
    }
  }
}
/* 
 * @author Miguel Ángel Liaño
 * @brief Interpretación en el juego del comando de avanzar a la derecha si está en una oca
 * @param game, Juego donde se interpreta el comando
 */
void game_callback_right(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  
  space_id = game_get_player_location(game);
  
  if (NO_ID == space_id) {
    return;
  }
  
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_east(game->spaces[i]);
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
      }
      return;
    }
  }
}
/*
 * @author Miguel Ángel Liaño
 * @brief Interpretación en el juego del comando de avanzar a la izquierda si está en una oca
 * @param game, Juego donde se interpreta el comando
 */
void game_callback_left(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;
  
  space_id = game_get_player_location(game);
  
  if (NO_ID == space_id) {
    return;
  }
  
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_west(game->spaces[i]);
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

/*
 * @author Miguel Ángel Liaño 
 * @brief Interpretación en el juego del comando de coger un objeto
 * @param game, Juego donde se interpreta el comando
 */
void game_callback_grasp(Game* game) {
  int i;
  Id object_id = NO_ID;
  Id player_id = NO_ID;
  Object *object = NULL;
  
  player_id = game_get_player_location(game);

  if(player_id == NO_ID || object_id == NO_ID ){
    return;
  }
  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) {
    object_id = object_get_location(game->objects[i]);
    if (object_id == player_id){
      object = game_get_object(game, object_id);
      player_set_object_id(game->player,object_get_id(object));
      game_set_object_location(game,(long)NULL,object);
    }  
  }
  return;      
}

/*
 * @author Carlos Miret Fiuza
 * @brief Interpretación en el juego del comando de soltar un objeto
 * @param game, Juego donde se interpreta el comando
*/
void game_callback_drop(Game* game) {

  Id player_id = NO_ID, id_object = NO_ID;
  int i;

  if (player_get_object_id(game->player) == NO_ID)
    return;
  
  player_id = game_get_player_location(game);
  id_object = player_get_object_id(game->player);

  if(player_id == NO_ID){
    return;
  }
  
  for(i = 0;i < MAX_OBJECTS && game->objects[i] != NULL ; i++){
    if(id_object == object_get_id(game->objects[i])){
      game_set_object_location(game,player_id,game->objects[i]);
      player_set_object_id(game->player,NO_ID);
    }
  }

return;
  
}
/*
 * @author Carlos Miret Fiuza
 * @brief Interpretación en el juego del comando de tirar el dado
 * @param game, Juego donde se interpreta el comando
*/
void game_callback_rollDie(Game* game) {
  game->dado = die_create(); 
  if(game->dado == NULL) return;
  
  die_roll(game->dado);

return;
}
