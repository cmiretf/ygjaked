/** 
 * @brief Como motor gráfico, este se ocupa de la distribucion de las diferentes pantallas que entran en juego del programa
 * 
 * @file graphic_engine.c
 * @author Miguel Ángel Liaño y Carlos Miret Fiuza
 * @version 1.0 
 * @date 10-2-2018 
 * @copyright GNU Public License
 */
#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "graphic_engine.h"

/*Distintas partes en la que quedará dividida la interfaz de juego*/
struct _Graphic_engine{ 
  Area *map; /*Mapa del juego*/
  Area *descript; /*Descripcion de comandos*/
  Area *banner; /*Información para la localizacion de objetos*/
  Area *help; /*Ayuda del juego*/
  Area *feedback; /*Información de comandos introducidos*/
};

/*
 * @author Carlos Miret Fiuza
 * @brief Crea y devuelve la interfaz de juego y la inicializa ( mapa, descripcion ...) 
 * @params void
 * @return puntero a Graphic_engine
 */
Graphic_engine *graphic_engine_create(){
  static Graphic_engine *ge = NULL;

  if (ge)
    return ge;
  
  screen_init();
  ge = (Graphic_engine *) malloc(sizeof(Graphic_engine));
  
  ge->map      = screen_area_init( 1, 1, 48, 13);
  ge->descript = screen_area_init(50, 1, 29, 13);
  ge->banner   = screen_area_init(28,15, 23,  1);
  ge->help     = screen_area_init( 1,16, 78,  2);
  ge->feedback = screen_area_init( 1,19, 78,  3);

  return ge;
}

/*
 * @author Carlos Miret Fiuza
 * @brief Borra la interfaz de juego pasada por argumento
 * @params puntero a Graphic_engine
 * @return void
 */
void graphic_engine_destroy(Graphic_engine *ge){
  if (!ge)
    return;
  
  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);
  
  screen_destroy();
  free(ge);
}

/*
 * @author Miguel Ángel Liaño
 * @brief Imprime en cada area del motor gráfico pasado como primer argumento, sus correspondientes datos del juego pasado como segundo argumento
 * @params puntero a Graphic_engine, y puntero a Game
 * @return void
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game){
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID;
  Id location_objects[MAX_OBJECTS];/*Array de id para la localizacion de los objetos*/
  Space* space_act = NULL;
  /*Object* object_act = NULL;*/
  const char *obj[MAX_OBJECTS];
  char str[255];
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[];
  int i;
  

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID){
    space_act = game_get_space(game, id_act);
    /*object_act = game_get_object(game, id_act);*/
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);

   /*Inicializamos el array contenedor de los nombres de los objetos*/
    for (i=0;i<MAX_OBJECTS;i++)
      obj[i] = "  ";

    /*Asignamos un nombre solamente a los objetos cuya localizacion coincida con id_back*/
    for (i=0;i<MAX_OBJECTS && game->objects[i]!=NULL;i++){
      if (game_get_object_location(game, game->objects[i]) == id_back){
        obj[i] = object_get_name(game->objects[i]);
      }
    }

   /*A pesar de imprimir todos los objetos se visualizaran los que tienen un nombre*/
    if (id_back != NO_ID) {
      sprintf(str, "  |         %2d|",(int) id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s %s %s %s|", obj[0], obj[1], obj[2], obj[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }

    for (i=0;i<MAX_OBJECTS;i++)
      obj[i] = "  ";

    /*Asignamos un nombre solamente a los objetos cuya localizacion coincida con id_act*/
    for (i=0;i<MAX_OBJECTS && game->objects[i]!=NULL;i++){
      if (game_get_object_location(game, game->objects[i]) == id_act){
        obj[i] = object_get_name(game->objects[i]);
      }
    }

    if (id_act != NO_ID) {
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | 8D      %2d|",(int) id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s %s %s %s|",obj[0], obj[1], obj[2], obj[3]);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }

    for (i=0;i<MAX_OBJECTS;i++)
      obj[i] = "  ";

    /*Asignamos un nombre solamente a los objetos cuya localizacion coincida con id_next*/
    for (i=0;i<MAX_OBJECTS && game->objects[i]!=NULL;i++){
      if (game_get_object_location(game, game->objects[i]) == id_next){
        obj[i] = object_get_name(game->objects[i]);
      }
    }

    if (id_next != NO_ID) {
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |         %2d|",(int) id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%s %s %s %s|",obj[0], obj[1], obj[2], obj[3]);
      screen_area_puts(ge->map, str);
    }
 
  }

  /* Paint the in the description area */
  screen_area_clear(ge->descript);
  for (i=0;i<MAX_OBJECTS;i++){
    location_objects[i] = game_get_object_location(game, game->objects[i]);
    if (location_objects[i] != NO_ID){
      sprintf(str, "Object %d Location:%d",i+1, (int)location_objects[i]);
      screen_area_puts(ge->descript, str);
    }
  }

  /* Paint the in the banner area */
  screen_area_puts(ge->banner, " The game of the Goose ");

  /* Paint the in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " following(f), previous(p), exit(e), grasp(g), drop(d), right(r), left(l) roll(x)");
  if( game_get_last_command(game) == ROLL || game_get_last_command(game) == 'x')
    sprintf(str, " Ultima tirada: %d", die_get_tirada(game->dado));
  screen_area_puts(ge->help, str);

  /* Paint the in the feedback area */
  last_cmd = game_get_last_command(game);
  sprintf(str, " %s", cmd_to_str[last_cmd-NO_CMD]);
  screen_area_puts(ge->feedback, str);
  
  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}
