/**
 * @file mi_io.c
 * @author Jose Ruben Cespedes Heredia
 * @date 9 Mar 2018
 * @brief Implementacion de las funciones que contiene la biblioteca propia.
 */

#include <dos.h>

#include "mi_io.h"

// Variables globales usadas en la implementacion
BYTE FG_COLOR = 7;	// Color del texto. Por defecto sera el 7, correspondiente al gris claro.
BYTE BG_COLOR = 0;	// Color de fondo. Por defecto sera el 0, correspondiente al negro.
int ALTO = 24;	// Alto de la consola
int ANCHO = 79;	// Ancho de la consola

/**
 * @brief Devuelve el color actual
 *
 * La funcion usa las variables globales BG_COLOR y FG_COLOR para obtener el decimal
 * que usaremos para escribir un caracter con el color de fondo y el color de texto
 * actual.
 *
 * @return Un entero que representa el codigo decimal del color actual.
 */
int getcolor(){
	int color = BG_COLOR << 4 | FG_COLOR;

	return color;
}

/**
 * @brief Avanza el cursor
 *
 * La funcion tiene en cuenta donde se encuentra el cursor actualmente y se mueve 
 * a la siguiente columna. En caso de haber llegado al final de la linea, avanzara
 * a la primera columna de la siguiente.
 */
void avanzar_cursor(){
	int linea = wherey();	// Linea actual
	int columna = wherex();	// Columna actual

	if(linea == ALTO && columna == ANCHO){	// Si estamos al final de la ultima linea, hacemos scrollup para poder seguir escribiendo
		scrollup(1, getcolor(), 0, 0, ALTO, ANCHO);
		linea = ALTO;
		columna = 0;
	} else if(columna < ANCHO){	// Si aun no hemos llegado al final del ancho, avanzamos una columna
		columna = columna + 1;
	} else {	// Si estamos al final del ancho, saltamos al principio de la siguiente linea
		linea = linea + 1;
		columna = 0;
	}

	gotoxy(columna, linea);
}

/**
 * @brief Indica si se ha pulsado alguna tecla
 *
 * La funcion llama a la subfuncion 1 de la interrupcion numero 16. Una
 * vez llamada, devuelve el registro cflag (zero flag), en el cual se
 * almacena un 0 si se ha pulsado una tecla y un 1 en caso contrario.
 *
 * @return devuelve el valor del registro zero flag
 */
int kbhit(){
	// Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
	// seleccionada y otro donde se guardan los datos devueltos por dicha interrupcion
	union REGS inregs, outregs;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "deteccion de tecla pulsada en bufer de teclado"
	inregs.h.ah = 0x01;

	// Mediante la funcion int86 llamamos a la interrupcion 0x16 que se asocia con la rutina de "gestion del teclado"
	int86(0x16, &inregs, &outregs);

	return outregs.x.cflag;
}

/**
 * @brief Indica la posición x actual del cursor
 *
 * La funcion llama a la subfuncion 3 de la interrupcion numero 10. Una
 * vez llamada, devuelve el registro dl, en el cual se
 * almacena la columna actual donde se encuentra el cursor.
 *
 * @return devuelve el valor del registro dl
 */
int wherex(){
	// Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
	// seleccionada y otro donde se guardan los datos devueltos por dicha interrupcion
	union REGS inregs, outregs;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "obtener tamaño y posicion del cursor"
	inregs.h.ah = 0x03;
	inregs.h.bh = 0x00;

	// Mediante la funcion int86 llamamos a la interrupcion 0x16 que se asocia con la rutina de "comunicacion con la tarjeta de video"
	int86(0x10, &inregs, &outregs);

	return outregs.h.dl;
}

/**
 * @brief Indica la posición y actual del cursor
 *
 * La funcion llama a la subfuncion 3 de la interrupcion numero 10. Una
 * vez llamada, devuelve el registro dh, en el cual se
 * almacena la fila actual donde se encuentra el cursor.
 *
 * @return devuelve el valor del registro dh
 */
int wherey(){
	// Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
	// seleccionada y otro donde se guardan los datos devueltos por dicha interrupcion
	union REGS inregs, outregs;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "obtener tamaño y posicion del cursor"
	inregs.h.ah = 0x03;
	inregs.h.bh = 0x00;

	// Mediante la funcion int86 llamamos a la interrupcion 0x16 que se asocia con la rutina de "comunicacion con la tarjeta de video"
	int86(0x10, &inregs, &outregs);

	return outregs.h.dh;
}

/**
 * @brief Mueve el cursor a una posicion determinada
 *
 * La funcion llama a la subfuncion 2 de la interrupcion numero 10. Dicha subfuncion
 * mueve el cursor a la posicion que se le indique
 *
 * @param x Indica la columna donde se quiere colocar el cursor
 * @param y Indice la fila donde se quiere colocar el cursor
 */
void gotoxy(int x, int y){
	// Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
	// seleccionada y otro donde se guardan los datos devueltos por dicha interrupcion
	union REGS inregs, outregs;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "colocar el cursor en una posicion determinada"
	inregs.h.ah = 0x02;

	// En el registro dx introducimos la fila y la columna donde queremos colocar el cursor
	inregs.h.bh = 0x00;
	inregs.h.dh = y;
	inregs.h.dl = x;

	// Mediante la funcion int86 llamamos a la interrupcion 0x16 que se asocia con la rutina de "comunicacion con la tarjeta de video"
	int86(0x10, &inregs, &outregs);
}


/**
 * @brief Fija el aspecto del cursor, debe admitir tres valores: INVISIBLE, NORMAL y GRUESO
 *
 * La funcion llama a la subfuncion 1 de la interrupcion numero 10. Dicha subfuncion
 * fija el aspecto del cursor en funcion de los numeros de linea que se le indiquen
 *
 * @param tipo_cursor Indica el tipo de cursor que desea establecer. Las opciones son INVISIBLE, NORMAL o GRUESO
 */
void setcursortype(enum types tipo_cursor){
	// Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
	// seleccionada y otro donde se guardan los datos devueltos por dicha interrupcion
	union REGS inregs, outregs;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "fijar el tamaño del cursor en modo texto"
	inregs.h.ah = 0x01;

	switch(tipo_cursor){
		case NORMAL:
			inregs.h.ch = 010;
			inregs.h.cl = 010;
			break;
		case GRUESO:
			inregs.h.ch = 000;
			inregs.h.cl = 010;
			break;
		case INVISIBLE:
			inregs.h.ch = 010;
			inregs.h.cl = 000;
			break;
	}

	// Mediante la funcion int86 llamamos a la interrupcion 0x10 que se asocia con la rutina de "comunicacion con la tarjeta de video"
	int86(0x10, &inregs, &outregs);
}

/**
* @brief Fija el modo de video deseado
*
* La funcion llama a la subfuncion 0 de la interrupcion numero 10. Dicha subfuncion
* fija el modo de video que se le indique.
*
* @param modo Es un caracter que indica el modo que se desea. Dicho caracter se debe traducir al decimal adecuado
*/
void setvideomode(BYTE modo){
	// Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
	// seleccionada y otro donde se guardan los datos devueltos por dicha interrupcion
	union REGS inregs, outregs;
	int modo_traducido;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "seleccionar modo de video"
	inregs.h.ah = 0x00;

	// Traducimos el caracter del modo en el decimal adecuado
	modo_traducido = traducir_caracter(modo);

	// Introducimos en el registro al el modo de video que deseamos establecer
	inregs.h.al = modo_traducido;

	ajustar_resolucion(modo_traducido);

	// Mediante la funcion int86 llamamos a la interrupcion 0x10 que se asocia con la rutina de "comunicacion con la tarjeta de video"
	int86(0x10, &inregs, &outregs);
}

void ajustar_resolucion(int nuevo_modo){
	switch(nuevo_modo){
		case '0':
			ANCHO = 39;
			ALTO = 24;
			break;
		case '1':
			ANCHO = 39;
			ALTO = 24;
			break;
		case '2':
			ANCHO = 79;
			ALTO = 24;
			break;
		case '3':
			ANCHO = 39;
			ALTO = 24;
			break;
		case '4':
			ANCHO = 319;
			ALTO = 199;
			break;
		case '5':
			ANCHO = 319;
			ALTO = 199;
			break;
		case '6':
			ANCHO = 639;
			ALTO = 199;
			break;
		case '7':
			ANCHO = 79;
			ALTO = 24;
			break;
		case '13':
			ANCHO = 319;
			ALTO = 199;
			break;
		case '14':
			ANCHO = 639;
			ALTO = 199;
			break;
		case '15':
			ANCHO = 639;
			ALTO = 349;
			break;
		case '16':
			ANCHO = 639;
			ALTO = 349;
			break;
		case '17':
			ANCHO = 639;
			ALTO = 479;
			break;
		case '18':
			ANCHO = 639;
			ALTO = 479;
			break;
		case '19':
			ANCHO = 319;
			ALTO = 199;
			break;
	}
}

/**
 * @brief Traduce un caracter al decimal adecuado para ser insertado en un registro
 *
 * La funcion usa un switch para relacionar cada caracter con el decimal adecuado
 *
 * @param caracter_original Es el caracter que deseamos traducir
 * @return un entero que representa el decimal del caracter traducido
 */
int traducir_caracter(BYTE caracter_original){
	int decimal;

	switch(caracter_original){
		case '0':
			decimal = 0;
			break;
		case '1':
			decimal = 1;
			break;
		case '2':
			decimal = 2;
			break;
		case '3':
			decimal = 3;
			break;
		case '4':
			decimal = 4;
			break;
		case '5':
			decimal = 5;
			break;
		case '6':
			decimal = 6;
			break;
		case '7':
			decimal = 7;
			break;
		case 'd':
			decimal = 13;
			break;
		case 'e':
			decimal = 14;
			break;
		case 'f':
			decimal = 15;
			break;
		case '10':
			decimal = 16;
			break;
		case '11':
			decimal = 17;
			break;
		case '12':
			decimal = 18;
			break;
		case '13':
			decimal = 19;
			break;
		default:
			decimal = 3;
			break;
	}

	return decimal;
}

/**
* @brief Obtiene el modo de video actual
*
* La funcion llama a la subfuncion 15 de la interrupcion numero 10. Dicha subfuncion nos devuelve el
* en el registro al el modo de video usado actualmente
*
* @return un entero que representa el modo de video actual
* @note la relacion entre los enteros y los modos de video se pueden observar en el fichero main.c
*/
int getvideomode(){
	// Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
	// seleccionada y otro donde se guardan los datos devueltos por dicha interrupciona
	union REGS inregs, outregs;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "averiguar el modo de video"
	inregs.h.ah = 0xF;

	// Mediante la funcion int86 llamamos a la interrupcion 0x10 que se asocia con la rutina de "comunicacion con la tarjeta de video"
	int86(0x10, &inregs, &outregs);

	return outregs.h.al;
}

/**
* @brief Modifica el color de primer plano con que se mostrarán los caracteres
*
* La funcion modifica la variable global FG_COLOR, la cual almacena el color en el que
* se escribe el texto por consola.
*/
void textcolor(int color){
	FG_COLOR = color;
}

/**
* @brief Modifica el color de fondo con que se mostrarán los caracteres
*
* La funcion modifica la variable global BG_COLOR, la cual almacena el color en el que
* se escribe el fondo de los caracteres por consola.
*/
void textbackground(int color){
	BG_COLOR = color;
}

/**
* @brief Borra toda la pantalla
*
* Esta funcion borra toda la pantalla haciendo que la funcion scrollup deslice la pantalla
* hacia arriba tantas lineas como alto tenga la consola. Ademas, situa el cursor en la posicion 0,0.
*
* @see scrollup(int lineas, int color, int lsi, int csi, int lid, int cid)
*/
void clrscr(){
	int color = BG_COLOR << 4 | FG_COLOR;

	scrollup(ALTO+1, color, 0, 0, ALTO, ANCHO);
	gotoxy(0,0);
}

/**
* @brief Borra una línea desde la posición actual del cursor hasta el final de la misma
*
* Esta funcion borra desde la posicion actual del cursor hasta el final de la linea (end of line, eof)
* haciendo uso de una de las caracteristicas de scrollup; y es que, cuando se llama a scrollup con el
* numero de lineas establecido en 0, se borra desde la (linea, columna) hasta la (linea, columna) que se
* desee
*
* @see scrollup(int lineas, int color, int lsi, int csi, int lid, int cid)
*/
void clreol(){
	int linea = wherey();	// Linea actual
	int columna = wherex();	// Columna actual

	int color = BG_COLOR << 4 | FG_COLOR;

	scrollup(0, color, linea, columna, linea, ANCHO);
}

/**
* @brief Desplaza toda la pantalla una línea hacia arriba
*
* La funcion llama a la subfuncion 6 de la interrupcion numero 10. Dicha subfuncion
* desplaza toda la pantalla hacia arriba el numero de lineas que se le indiquen. Si 
* se le indican 0 lineas, borra la pantalla entre los puntos que se quieran (mediante lsi, csi, lid, cid.
*
* @param lineas Numero de lineas que se desean desplazar. 0 para borrar.
* @param color Color de relleno para los espacios en blanco. Los tres primeros bits indican el color de fondo
* y los tres ultimos el color del texto.
* @param lsi Linea superior izquierda. Linea inicial desde la que se desea comenzar a desplazar/borrar.
* @param csi Columna superior izquierda. Columna inicial desde la que se desea comenzar a desplazar/borrar.
* @param lid Linea inferior derecha. Linea final hasta la que se desea desplazar/borrar.
* @param cid Columna inferior derecha. Columna final hasta la que se desea desplazar/borrar.
*/
void scrollup(int lineas, int color, int lsi, int csi, int lid, int cid){
	// Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
	// seleccionada y otro donde se guardan los datos devueltos por dicha interrupcion
	union REGS inregs, outregs;
	
	// En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "desplazar zona de pantalla hacia arriba"
	inregs.h.ah = 0x06;

	// En el resto de registros introducimos todos los parametros descritos anteriormente
	inregs.h.al = lineas;
	inregs.h.bh = color;
	inregs.h.ch = lsi;
	inregs.h.cl = csi;
	inregs.h.dh = lid;
	inregs.h.dl = cid;

	// Mediante la funcion int86 llamamos a la interrupcion 0x10 que se asocia con la rutina de "comunicacion con la tarjeta de video"
	int86(0x10, &inregs, &outregs);

	// Una vez realizado el desplazamiento de la pantalla, desplazamos el cursor un mismo numero de lineas
	gotoxy(wherex(),wherey()-lineas);
}

/**
* @brief Desplaza toda la pantalla una línea hacia abajo
*
* La funcion llama a la subfuncion 7 de la interrupcion numero 10. Dicha subfuncion
* desplaza toda la pantalla hacia abajo el numero de lineas que se le indiquen. Si 
* se le indican 0 lineas, borra la pantalla entre los puntos que se quieran (mediante lsi, csi, lid, cid.
*
* @param lineas Numero de lineas que se desean desplazar. 0 para borrar.
* @param color Color de relleno para los espacios en blanco. Los tres primeros bits indican el color de fondo
* y los tres ultimos el color del texto.
* @param lsi Linea superior izquierda. Linea inicial desde la que se desea comenzar a desplazar/borrar.
* @param csi Columna superior izquierda. Columna inicial desde la que se desea comenzar a desplazar/borrar.
* @param lid Linea inferior derecha. Linea final hasta la que se desea desplazar/borrar.
* @param cid Columna inferior derecha. Columna final hasta la que se desea desplazar/borrar.
*/
void scrolldown(int lineas, int color, int lsi, int csi, int lid, int cid){
	// Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
	// seleccionada y otro donde se guardan los datos devueltos por dicha interrupcion
	union REGS inregs, outregs;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "desplazar zona de pantalla hacia abajo"
	inregs.h.ah = 0x07;

	inregs.h.al = lineas;
	inregs.h.bh = color;
	inregs.h.ch = lsi;
	inregs.h.cl = csi;
	inregs.h.dh = lid;
	inregs.h.dl = cid;

	// Mediante la funcion int86 llamamos a la interrupcion 0x10 que se asocia con la rutina de "comunicacion con la tarjeta de video"
	int86(0x10, &inregs, &outregs);
}

/**
* @brief Escribe un caracter en pantalla con el color indicado actualmente
*
* La funcion llama a la subfuncion 9 de la interrupcion numero 10. Dicha subfuncion
* imprime un caracter por pantalla con el color indicado y el numero de veces que se desee.
* Finalmente avanza el cursor.
*
* @param caracter Caracter que se desea imprimir
* @param repeticiones Numero de veces que se desea imprimir el caracter
* @see avanzar_cursor
*/
void cputchar(const char caracter, int repeticiones){
	// Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
	// seleccionada y otro donde se guardan los datos devueltos por dicha interrupcion
	union REGS inregs, outregs;
	int color = BG_COLOR << 4 | FG_COLOR;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "escribir un caracter en pantalla"
	inregs.h.ah = 0x09;

	// En el resto de registros se introducen el caracter, el color y el numero de veces que se desea imprimir el caracter
	inregs.h.al = caracter;
	inregs.h.bl = color;
	inregs.h.bh = 0x00;
	inregs.x.cx = repeticiones;

	// Mediante la funcion int86 llamamos a la interrupcion 0x10 que se asocia con la rutina de "comunicacion con la tarjeta de video"
	int86(0x10, &inregs, &outregs);

	// Finalmente avanzamos el cursor
	avanzar_cursor();
}

/**
* @brief Obtiene el caracter de teclado y lo muestra en pantalla
*
* La funcion llama a la subfuncion 0 de la interrupcion numero 10. Dicha subfuncion
* lee un caracter desde el teclado y lo almacena en el registro al. En caso de ser
* una tecla especial queda almacenado en el ah.
*
* @return Decimal que representa el caracter introducido por teclado
*/
int getche(){
	// Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
	// seleccionada y otro donde se guardan los datos devueltos por dicha interrupcion
	union REGS inregs, outregs;
	int caracter;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "leer un caracter desde el teclado"
	inregs.h.ah = 0x00;

	// Mediante la funcion int86 llamamos a la interrupcion 0x16 que se asocia con la rutina de "gestion del teclado"
	int86(0x16, &inregs, &outregs);

	// Si al es 0 significa que es un caracter especial. 1 en caso contrario
	if(outregs.h.al != 0)
		caracter = outregs.h.al;
	else
		caracter = outregs.h.ah;

	cputchar(caracter, 1);

	return caracter;
}


/**
* @brief Obtiene el caracter de teclado
*
* La funcion llama a la subfuncion 0 de la interrupcion numero 10. Dicha subfuncion
* lee un caracter desde el teclado y lo almacena en el registro al. En caso de ser
* una tecla especial queda almacenado en el ah.
*
* @return Decimal que representa el caracter introducido por teclado
*/
int getch(){
	// Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
	// seleccionada y otro donde se guardan los datos devueltos por dicha interrupcion
	union REGS inregs, outregs;
	int caracter;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "leer un caracter desde el teclado"
	inregs.h.ah = 0x00;

	// Mediante la funcion int86 llamamos a la interrupcion 0x16 que se asocia con la rutina de "gestion del teclado"
	int86(0x16, &inregs, &outregs);

	// Si al es 0 significa que es un caracter especial. 1 en caso contrario
	if(outregs.h.al != 0)
		caracter = outregs.h.al;
	else
		caracter = outregs.h.ah;

	return caracter;
}

/**
* @brief Imprime una cadena de caracteres en pantalla
*
* La funcion hace uso de la funcion cputchar para ir imprimiendo por pantalla
* uno a uno los caracteres de la cadena que se desea imprimir. Lo que hacemos es que
* vamos leyendo los caracteres de la cadena introducida hasta llegar al caracter
* de fin de linea ('\0'). Si el caracter es distinto del de salto de linea (\n)
* lo imprimimos y avanzamos al siguiente caracter. Si el caracter leido es el de 
* salto de linea, situamos el cursor al inicio de la siguiente linea y avanzamos
* el indice para leer el siguiente caracter
*
* @param cadena Cadena que se desea imprimir
* @return decimal que representa al ultimo caracter leido
*/
int cputs(const char * cadena){
	int i = 0;	// Indice para recorrer la cadena
	int linea = wherey();	// Linea actual
	int columna = wherex();	// Columna actual

	while(cadena[i] != '\0'){
		if(cadena[i] != '\n')
			cputchar(cadena[i],1);
		else {
			columna = 0;

			if(linea < ALTO)
				linea = linea + 1;
			else {
				scrollup(1, getcolor(), 0, 0, ALTO, ANCHO);
				linea = ALTO;
			}

			gotoxy(columna, linea);
		}

		i = i+1;	// Avanzamos el indice
	}

	return cadena[i];
}