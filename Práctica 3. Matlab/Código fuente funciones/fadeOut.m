% Realiza un efecto de fade-out durante los 3 ultimos segundos
%atenuada=fadeOut(sound, 8192, 3.0);

% Produce un efecto de desvanecimiento lineal unos segundos antes de la
% señal pasada como argumento
function [y] = fadeOut(signal, frecMuestreo, duracion)

% Numero de muestras que tiene el tramo de señal que queremos modificar
num = frecMuestreo*duracion;

% Partimos la señal inicial en dos subseñales. Una parte es la que no
% modificaremos y la otra es a la que debemos aplicar el efecto
subsignal_original = signal(1:end-num);
subsignal_effect = signal(end-num+1:end);

% Creamos un vector rampa con el mismo numero de elementos que muestras
% vamos a modificar
rampa = linspace(1,0,num);

% Transponemos el vector rampa para que su tamaño coincida con el de la
% subseñal que tenemos que modificar
rampa_transpose = transpose(rampa);

% Modificamos la subseñal a la que teniamos que aplicar el efecto
% multiplicandola por el vector rampa traspuesto
signal_effect = subsignal_effect.*rampa_transpose;

% Concatenamos la subseñal que no teniamos que modificar con la nueva
% subseñal con el efecto aplicado
y = cat(1,subsignal_original, signal_effect);
end