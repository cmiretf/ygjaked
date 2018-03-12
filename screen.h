/** 
 * @file screen.h
 * @author Miguel Ángel Liaño y Carlos Miret Fiuza
 * @version 1.0 
 * @date 10-2-2018 
 * @copyright GNU Public License
 */

#ifndef __SCREEN__
#define __SCREEN__

#define SCREEN_MAX_STR 80

typedef struct _Area Area;

/*
 * @author Carlos Miret Fiuza
 * @brief Inicializa la pantalla de juego apartir del fichero dado como variable global
 * @params void
 * @return void
 */
void  screen_init();

/*
 * @author Miguel Ángel Liaño
 * @brief Borra la pantalla de juego
 * @params void
 * @return void
 */
void  screen_destroy();

/*
 * @author Carlos Miret Fiuza
 * @brief Imprime la pantalla de juego a partir del fichero dado como variable global
 * @params void
 * @return void
 */
void  screen_paint();

/*
 * @author Miguel Ángel Liaño 
 * @brief Enseña por pantalla el prompt para que los datos sean introducidos por el usuario
 * @params void
 * @return void
 */
void  screen_gets(char *str);

/*
 * @author Carlos Miret Fiuza
 * @brief Devuelve el area dada la altura, anchura, longitude en eje x e y pasados por argumentos
 * @params x ,y ,width , height de tipo int
 * @return puntero a Area
 */
Area* screen_area_init(int x, int y, int width, int height);

/*
 * @author Miguel Ángel Liaño 
 * @brief Borrar el aŕea pasada por agumento
 * @params void
 * @return void
 */
void  screen_area_destroy(Area* area);

/*
 * @author Carlos Miret Fiuza
 * @brief Limpia el área del juego pasado como argumento
 * @params void
 * @return void
 */
void  screen_area_clear(Area* area); 

/*
 * @author Miguel Ángel Liaño 
 * @brief Reajusta el cursor de un área dada como argumento
 * @params void
 * @return void
 */
void  screen_area_reset_cursor(Area* area);

/*
 * @author Carlos Miret Fiuza
 * @brief Si el cursor se desvia de la "trayectoria", esta funcion la reajusta
 * @params void
 * @return void
 */
void  screen_area_puts(Area* area, char *str);



#endif
