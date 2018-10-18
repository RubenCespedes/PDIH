/**
 * @file main.c
 * @author Jose Ruben Cespedes Heredia
 * @date 9 Mar 2018
 * @brief Funcion principal que ejecuta en secuencia las funciones
 * implementadas en la biblioteca propia.
 */

#include "mi_io.h"

//////////////*	COLORES    *///////////////
/*	COLORES			VALOR	FONDO/TEXTO
	 Negro		 	 0		 Ambos
	 Azul 		 	 1		 Ambos
	 Verde		 	 2		 Ambos
	 Cian		 	    3		 Ambos
	 Rojo 		 	 4		 Ambos
	 Magenta	 	    5		 Ambos
	 Marron		 	 6		 Ambos
	 Gris Claro	 	 7		 Ambos
	 Gris Oscuro 	 8		 Texto
	 Azul Claro	 	 9		 Texto
	 Verde Claro 	 10	 Texto
	 Cian Claro	 	 11	 Texto
	 Rojo Claro		 12	 Texto
	 Magenta Claro	 13	 Texto
	 Amarillo		 14	 Texto
	 Blanco			 15	 Texto
	 Parpadeo		 128	 Texto */

//////////////*	MODO DE VIDEO    *///////////////
/*	MODO 	TIPO 	RESOLUCION 		COLORES
	 0h	texto 	  40x25		 16 tonos de gris
	 1h 	texto 	  40x25		 16 colores
	 2h	texto 	  80x25		 16 tonos de gris
	 3h	texto 	  80x25		 16 colores
	 4h	grafico	 320x200		 4 colores
	 5h	grafico	 320x200		 4 colores
	 6h	grafico	 640x200		 2 colores
	 7h	texto 	  80x25		 monocromo
	 dh	grafico	 320x200		 16 colores
	 eh	grafico	 640x200		 16 colores
	 fh	grafico	 640x350		 monocromo
	 10h	grafico	 640x350		 16 colores
	 11h	grafico	 640x480		 2 colores
	 12h	grafico	 640x480		 16 colores
	 13h	grafico	 320x200		 256 colores */

int main() {
	int color;
	enum types tipo_cursor = NORMAL;
	int linea, columna;

	clrscr();
   	cputs("Pulse una tecla para continuar (prueba del kbhit):");
   	while(!kbhit());
   	cprintf("\r\nTecla pulsada...\r\n",getch());
   	getch();
   	cputs("Prueba del gotoxy. Voy a avanzar una linea en Y y 10 caracteres en X. Pulse una tecla para continuar.\n");
   	linea = wherey() + 1;
   	columna = wherex() + 10;
   	gotoxy(columna,linea);
   	// El +1 siguiente se debe a que wherex y wherey comienzan en 0, pero nosotros empezamos contando en 1
   	cprintf("Prueba del wherex/y. El cursor esta en (X=%d,Y=%d). Pulse una tecla para continuar.\r\n",columna+1,linea+1);
   	getch();
   	cputs("Prueba del clrscr. Pulse una tecla para borrar la pantalla.\n");
   	getch();
   	clrscr();
   	cputs("Pantalla borrada. A partir de este punto voy a borrar la linea.\n");
   	cputs("Pantalla borrada. A partir de este punto NO voy a borrar la linea.");
   	getch();
   	gotoxy(40,0);
   	clreol();
   	getch();
   	clrscr();
   	cputs("Cambiamos de color. FG=RED, BG=BLUE\n");
   	getch();
   	textcolor(4);
   	textbackground(1);
   	cputchar('P',1);
   	getch();
   	textcolor(7);	// COLOR DE FUENTE POR DEFECTO
   	textbackground(0); // FONDO AZUL PARA HACER EL CLEAR SCREAN
   	clrscr();
   	cputs("Borrar pantalla en fondo azul. Despues ponemos fondo rojo\n");
   	getch();
   	textbackground(1); // FONDO AZUL
   	clrscr();
    cputs("\nAhora hacemos scrollup de 1 linea\n");
   	getch();
   	cputs("\nAhora hacemos scrolldown de 1 linea\n");
   	textbackground(4); // FONDO ROJO PARA EL SCROLL
   	color = getcolor();
   	scrollup(1, color, 0, 0, 24, 79);
   	getch();
   	scrolldown(1, color, 0, 0, 24, 79);
   	getch();
   	clrscr();
   	cputs("\nCursor invisible: ");
   	tipo_cursor = INVISIBLE;
   	setcursortype(tipo_cursor);
   	getch();
   	cputs("\nCursor grueso: ");
   	tipo_cursor = GRUESO;
   	setcursortype(tipo_cursor);
   	getch();
   	cputs("\nCursor normal: ");
   	tipo_cursor = NORMAL;
   	setcursortype(tipo_cursor);
   	getch();
   	cputs("\nCambiar a modo de video 0x1 (40x25)");
   	getch();
   	textbackground(0);
   	clrscr();
   	setvideomode('d');
   	cputs("Restituir modo de video");
   	getch();
   	setvideomode(3);
   	clrscr();
   	cputs("Pulse una tecla para finalizar\n");
   	getch();
   	textcolor(7);
   	textbackground(0);
   	cputs("Programa finalizado\n\n");
   	getch();

   	return 0;
}
