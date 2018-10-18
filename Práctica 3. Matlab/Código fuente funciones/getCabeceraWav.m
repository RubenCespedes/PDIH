% Obtiene los principales valores de la cabecera del fichero WAV pasado
% como argumento
function [canales, frecMuestreo, resolucion, numeroBytesMuestras] = getCabeceraWav(fichero)

% Abrimos el fichero pasado como argumento con acceso de lectura binaria
% con ordenacion Little-endian
fileID = fopen(fichero,'r','l');

% Nos movemos a una determinada posicion en el fichero. En este caso, al
% byte 21 que corresponde con la posicion del primer dato a obtener
fseek(fileID, 21, 0);

% Leemos 2 datos de un fichero binario interpretando cada valor en el fichero
% como un byte ('*ubit8'). [El campo 'Nº de canales' ocupa 2 Bytes]
canales = fread(fileID, 2, '*ubit8');

% Igual que el anterior, pero leemos 4 datos. [El campo 'Frec. de muestreo
% en hertzios' ocupa 4 Bytes]
frecMuestreo = fread(fileID, 4, '*ubit8');

% Avanzamos 4 posiciones en el fichero. [Nos saltamos el campo 'Bytes por
% segundo' que ocupa 4 Bytes]
fseek(fileID, 4, 0);

% Leemos 2 datos. [El campo 'Bytes por muestra' ocupa 2 Bytes]
numeroBytesMuestras = fread(fileID, 2, '*ubit8');

% Leemos 2 datos. [El campo 'Resolucion' en bits ocupa 2 Bytes]
resolucion = fread(fileID, 2, '*ubit8');

% Cerramos el fichero abierto
fclose(fileID);

end