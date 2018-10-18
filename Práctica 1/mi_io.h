#ifndef BYTE
	#define BYTE unsigned char
#endif

enum types { INVISIBLE, NORMAL, GRUESO };

// Indica si se ha pulsado alguna tecla
int kbhit();

// Indica la posición x actual del cursor
int wherex();

// Indica la posición y actual del cursor
int wherey();

// Mueve el cursor a la posición según las coordenadas especificadas por los argumentos x e y
void gotoxy(int x, int y);

// Fija el aspecto del cursor, debe admitir tres valores: INVISIBLE, NORMAL y GRUESO
void setcursortype(enum types);

// Fija el modo de video deseado
void setvideomode(BYTE modo);

void ajustar_resolucion(int nuevo_modo);

// Obtiene el modo de video actual
int getvideomode();

// Modifica el color de primer plano con que se mostrarán los caracteres
void textcolor(int color);

// Modifica el color de fondo con que se mostrarán los caracteres
void textbackground();

// Borra toda la pantalla
void clrscr();

// Borra una línea desde la posición actual del cursor hasta el final de la misma
void clreol();

// Desplaza toda la pantalla una línea hacia arriba
void scrollup(int n_lineas, int color, int lsi, int csi, int lid, int cid);

// Desplaza toda la pantalla una línea hacia abajo
void scrolldown(int n_lineas, int color, int lsi, int csi, int lid, int cid);

// Escribe un caracter en pantalla con el color indicado actualmente
void cputchar(const char, int);

// Obtiene el caracter de teclado y lo muestra en pantalla
int getche();

// Obtiene un caracter desde el teclado
int getch();

// Imprime una cadena de caracteres en pantalla
int cputs(const char * cadena);

// Devuelve el color actual en decimal (mezcla de color de fondo y el color de texto)
int getcolor();

// Avanza el cursor: una columna (si puede) o una linea y reinicia la columna a 0
void avanzar_cursor();