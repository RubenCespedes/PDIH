% Reproduce el sonido pasado como parametro a la frecuencia y resolucion
% indicadas. Ademas, se podra reproducir solo un intervalo de tiempo de
% dicho sonido
function [y] = reproduceSonido(signal, fMuest, resol, t_ini, t_fin)   
switch nargin
    case 3
    % Si hemos introducido 3 argumentos, reproducimos el sonido a
    % la frecuencia de muestreo y la resolucion indicada, y
    sound(signal, fMuest, resol);
    % Devolvemos la señal
    y = signal;
    
    case 5
    % Si hemos introducido 5 argumentos
            
    if t_ini > t_fin
        % Si el tiempo inicial es mayor que el final, los
        % intercambiamos
        t_aux = t_ini;
        t_ini = t_fin;
        t_fin = t_aux;
    end
            
    % Obtenemos la posicion de la primera muestra a reproducir
    muestra_ini = fix(t_ini*fMuest);
    % Obtenemos la posicion de la ultima muestra a reproducir
    muestra_fin = fix(t_fin*fMuest);
    
    if muestra_fin > size(signal, 1)
        % Si la posicion de la ultima muestra a reproducir
        % sobrepasa el tamaño de la señal, la sobreescribimos
        muestra_fin = size(signal, 1);
    end
            
    % Obtenemos la subseñal a reproducir
    y = signal(muestra_ini:muestra_fin, :);
            
    % Escalamos los datos y reproducimos la subseñal a la
    % frecuencia de muestreo y resolucion indicados
    soundsc(y, fMuest, resol);
end  
end