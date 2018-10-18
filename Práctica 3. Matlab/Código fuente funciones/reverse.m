% Ejemplo de llamada a la funcion
%alreves = reverse(sound);

function [y] = reverse(signal)
% La señal recibida tiene una columna y x filas. Damos la vuelta de arriba
% a abajo a dicha columna
y = flipud(signal);
end