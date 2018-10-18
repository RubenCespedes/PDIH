% Captura sonido desde la linea de entrada de la tarjeta de sonido y lo
% graba con los parametros pasados como argumentos en el fichero indicado
function [y] = grabaSonido(fichero, frecMuestreo, resolucion, canales, duracion)

% Creamos un objeto para grabar audio y establecemos la frecuencia de
% muestreo, la resolucion, el numero de canales y el identificador de la
% tarjeta de sonido (0)
recorder = audiorecorder(frecMuestreo, resolucion, canales, 0);

% Mostramos un mensaje para informar al usuario que se va a proceder a
% grabar audio
disp('Start speaking.');

% Grabamos audio en el objeto 'recorder' durante los segundos pasados como
% parametro, manteniendo el control hasta que se haya completado la
% grabacion
recordblocking(recorder, duracion);

% Mostramos un mensaje para informar al usuario que la grabacion de audio
% ha terminado
disp('End of recording.');

% Almacenamos la senal de audio grabada en un array numerico de 'double'
% [rango de valores de la muestra entre -1 y 1]
myRecording = getaudiodata(recorder, 'double');

% Abrimos o creamos el fichero pasado como argumento con acceso para
% escribir, descartando el contenido existente
fileID = fopen(fichero,'w');

% Escribimos la senal de audio grabada en el fichero pasado como argumento,
% estableciendo los valores a escribir como Bytes y que el orden en el que
% se deben de escribir es 'Little Endian'
fwrite(fileID, myRecording, 'ubit8', 'l');

% Cerramos el archivo abierto
fclose(fileID);

% Devolvemos la senal de audio grabada
y = myRecording;

end