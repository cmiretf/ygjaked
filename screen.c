
/** 
 * @brief La tarea principal es implementar las diferentes funciones que se encargan de la visualizacion del mapa
 * 
 * @file screen.c
 * @author Miguel Ángel Liaño y Carlos Miret Fiuza
 * @version 1.0 
 * @date 10-2-2018 
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"

#pragma GCC diagnostic ignored "-Wpedantic"

/*Numero maximo de filas*/
#define ROWS 23 
/*Numero maximo de columnas*/
#define COLUMNS 80 
/*Tamaño maximo del mapa*/
#define TOTAL_DATA (ROWS * COLUMNS) + 1 

#define BG_CHAR '~'
#define FG_CHAR ' '
#define PROMPT " prompt:> "

#define ACCESS(d, x, y) (d + ((y) * COLUMNS) + (x))

/*Se definen los datos de la estructura área*/
struct _Area{ 
  int x; /*Eje x*/
  int y; /*Eje y*/
  int width; /*Anchura del area*/
  int height; /*Altura del area*/
  char *cursor; /*Referencia del cursor*/
};

/*Variable global*/
char *__data;

/****************************/
/*     Private functions    */
/****************************/
/*
 * @author Miguel Ángel Liaño 
 * @brief Devuelve una posición dentro de los límites del área dada por argumento
 * @params area de tipo Area
 * @return int con las coordenadas
 */
int  screen_area_cursor_is_out_of_bounds(Area* area);
/*
 * @author Carlos Miret Fiuza
 * @brief Desplaza hacia arriba el cursor, a partir de un área dada por argumento
 * @params area de tipo Area
 * @return void
 */
void screen_area_scroll_up(Area* area);
/*
 * @author Miguel Ángel Liaño 
 * @brief Desplaza hacia arriba el cursor, a partir de un área dada por argumento
 * @params str puntero a char
 * @return void
 */
void screen_utils_replaces_special_chars(char* str);

/****************************/
/* Functions implementation */
/****************************/


/*
 * @author Carlos Miret Fiuza
 * @brief Inicializa la pantalla de juego apartir del fichero dado como variable global
 * @params void
 * @return void
 */
void screen_init(){
  screen_destroy(); /* Dispose if previously initialized */
  __data = (char *) malloc(sizeof(char) * TOTAL_DATA);

  if (__data){
    memset(__data, (int) BG_CHAR, TOTAL_DATA); /*Fill the background*/
    *(__data + TOTAL_DATA - 1) = '\0';         /*NULL-terminated string*/
  }
}

/*
 * @author Miguel Ángel Liaño 
 * @brief Borra la pantalla de juego
 * @params void
 * @return void
 */
void screen_destroy(){
  if (__data)
    free(__data);
}

/*
 * @author Carlos Miret Fiuza
 * @brief Imprime la pantalla de juego a partir del fichero dado como variable global
 * @params void
 * @return void
 */
void screen_paint(){
  char *src = NULL;
  char dest[COLUMNS + 1];
  int i=0;

  memset(dest, 0, COLUMNS + 1);
  
  if (__data){
    /* puts(__data); */ /*Dump data directly to the terminal*/
    /*It works fine if the terminal window has the right size*/
    
    puts("\033[2J"); /*Clear the terminal*/
    for (src=__data; src < (__data + TOTAL_DATA - 1); src+=COLUMNS){
      memcpy(dest, src, COLUMNS);
      /* printf("%s\n", dest); */
      for (i=0; i<COLUMNS; i++){
	if (dest[i] == BG_CHAR){
	  printf("\033[0;34;44m%c\033[0m", dest[i]); /* fg:blue(34);bg:blue(44) */
	}else{
	  printf("\033[0;30;47m%c\033[0m", dest[i]); /* fg:black(30);bg:white(47)*/
	}
      }
      printf("\n");
    }
  }
}

/*
 * @author Miguel Ángel Liaño
 * @brief Enseña por pantalla el prompt para que los datos sean introducidos por el usuario
 * @params void
 * @return void
 */
void screen_gets(char *str){
  fprintf(stdout, PROMPT);
  if (fgets(str, COLUMNS, stdin))
    *(str + strlen(str) - 1) = 0; /* Replaces newline character with '\0' */
}

/*
 * @author Carlos Miret Fiuza
 * @brief Devuelve el area dada la altura, anchura, longitude en eje x e y pasados por argumentos
 * @params x ,y ,width , height de tipo int
 * @return puntero a Area
 */
Area* screen_area_init(int x, int y, int width, int height){
  int i = 0;
  Area* area = NULL;

  if ( (area  = (Area*) malloc (sizeof(struct _Area))) ){
    *area = (struct _Area) {x, y, width, height, ACCESS(__data, x, y)};

    for (i=0; i < area->height; i++)
      memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
  }

  return area;
}

/*
 * @author Miguel Ángel Liaño
 * @brief Borrar el aŕea pasada por agumento
 * @params void
 * @return void
 */
void screen_area_destroy(Area* area){
  if(area)
    free(area);
}

/*
 * @author Carlos Miret Fiuza
 * @brief Limpia el área del juego pasado como argumento
 * @params void
 * @return void
 */
void screen_area_clear(Area* area){
  int i = 0;

  if (area){
    screen_area_reset_cursor(area);
    
    for (i=0; i < area->height; i++)
      memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
  }
}

/*
 * @author Miguel Ángel Liaño
 * @brief Reajusta el cursor de un área dada como argumento
 * @params void
 * @return void
 */
void screen_area_reset_cursor(Area* area){
  if (area)
    area->cursor = ACCESS(__data, area->x, area->y);
}

/*
 * @author Carlos Miret Fiuza
 * @brief Si el cursor se desvia de la "trayectoria", esta funcion la reajusta
 * @params void
 * @return void
 */
void screen_area_puts(Area* area, char *str){
  int len = 0;
  char *ptr = NULL;

  if (screen_area_cursor_is_out_of_bounds(area))
    screen_area_scroll_up(area);
  
  screen_utils_replaces_special_chars(str);

  for (ptr = str; ptr < (str + strlen(str)); ptr+=area->width){
    memset(area->cursor, FG_CHAR, area->width);
    len = (strlen(ptr) < area->width)? strlen(ptr) : area->width;
    memcpy(area->cursor, ptr, len);
    area->cursor += COLUMNS;
  }
}

/*
 * @author Miguel Ángel Liaño
 * @brief Devuelve una posición dentro de los límites del área dada por argumento
 * @params area de tipo Area
 * @return int con las coordenadas
 */
int screen_area_cursor_is_out_of_bounds(Area* area){
  return area->cursor > ACCESS(__data, area->x + area->width, area->y + area->height - 1);
}

/*
 * @author Carlos Miret Fiuza
 * @brief Desplaza hacia arriba el cursor, a partir de un área dada por argumento
 * @params area de tipo Area
 * @return void
 */
void screen_area_scroll_up(Area* area){
  for(area->cursor = ACCESS(__data, area->x, area->y);
      area->cursor < ACCESS(__data, area->x + area->width, area->y + area->height - 2);
      area->cursor += COLUMNS){
    memcpy(area->cursor, area->cursor+COLUMNS, area->width);
  }
}

/*
 * @author Miguel Ángel Liaño 
 * @brief Desplaza hacia arriba el cursor, a partir de un área dada por argumento
 * @params str puntero a char
 * @return void
 */
void screen_utils_replaces_special_chars(char* str){
  char *pch = NULL;

  /* Replaces acutes and tilde with '??' */
  while ((pch = strpbrk (str, "ÁÉÍÓÚÑáéíóúñ")))
    memcpy(pch, "??", 2);
}
