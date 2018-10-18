% Dibujar la forma de onda de cada uno de los canales de los que consta el
% sonido pasado como parametro
function dibujaSonido(signal,titulo)    

% Guardamos la señal del primer canal del sonido
channel1 = signal(:,1);
    
% Si existe un segundo canal, guardamos tambien su señal
if size(signal,2) > 1
    channel2 = signal(:,2);
end
    
% Dividimos la figura actual (ventana) en una rejilla de 2 filas y una
% columna y seleccionamos la primera grafica
subplot(2,1,1);
    
    % El eje x de la primera grafica se encontrara entre 1 y el numero de
    % muestras del primer canal
    x = linspace(0, length(channel1), length(channel1));
    % El eje y sera el valor de las muestras del primer canal
    y = channel1;
    % Dibujamos la primera grafica
    plot(x, y);
    
    switch nargin
        case 2
            % Si hemos introducido algun titulo, insertamos dicho titulo
            % mas el numero del canal en la grafica
            title(strcat(titulo,'1'));
            
            if size(signal,2) > 1
                % Si hay un segundo canal, lo mostramos del mismo modo que
                % el anterior
                subplot(2,1,2);
                x = linspace(0, length(channel2), length(channel2));
                y = channel2;
                plot(x, y);
                title(strcat(titulo,'2'));
            end
        case 1
            % Si no se ha introducido ningun titulo, ponemos un titulo por
            % defecto
            title('Canal 1');
            
            if size(signal,2) > 1
                % Si hay un segundo canal, lo mostramos del mismo modo que
                % el anterior
                subplot(2,1,2);
                x = linspace(0, length(channel2), length(channel2));
                y = channel2;
                plot(x, y);
                title('Canal 2');
            end
    end
end

