#include "MiLib.h"
#include <stdio.h>

/* Modos de video
	Modo 	Tipo	Resolucion	Colores
	0h		texto	 40x25		 16 tonos de gris
	1h 		texto	 40x25		 16 colores
	2h		texto	 80x25		 16 tonos de gris
	3h		texto	 80x25		 16 colores
	4h		grafico	 320x200	 4 colores
	5h		grafico	 320x200	 4 colores
	6h		grafico	 640x200	 2 colores
	7h		texto	 80x25		 monocromo
	dh		grafico	 320x200	 16 colores
	eh		grafico	 640x200	 16 colores
	fh		grafico	 640x350	 monocromo
	10h		grafico	 640x350	 16 colores
	11h		grafico	 640x480	 2 colores
	12h		grafico	 640x480	 16 colores
	13h		grafico	 320x200	 256 colores
*/

int main(){
	unsigned char modo;
	
	printf("%s\n", "Introduzca un valor numerico para definir el modo de video");
	scanf("%d", &modo);

	selecciona_modo_video(modo);

	printf("%s\n", "Con esta salida comprobamos el cambio de modo de video. Pulse cualquier tecla para salir");
	scanf("%d", &modo);
	selecciona_modo_video(3);

	return(0);
}