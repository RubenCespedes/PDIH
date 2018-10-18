#include <dos.h>
#include "MiLib.h"
#define BYTE unsigned char

/* Selecciona el modo de video deseado */
void selecciona_modo_video(BYTE modo){
	// Tenemos dos registros, uno donde pasamos los parametros de entrada y otro donde obtenemos los resultados
	union REGS inregs, outregs;

	// En la parte ALTA del registro de entrada introducimos la subfuncion, en este caso, es "seleccionar modo de video"
	inregs.h.ah = 0x00;

	// En la parte BAJA pasamos los parametros, en este caso, el modo de video
	inregs.h.al = modo;

	// Mediante la funcion int86 llamamos a la interrupcion 0x10 que se asocia con la rutina de "servicios de video"
	int86(0x10, &inregs, &outregs);
	return;
}