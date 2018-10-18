
function [y] = insertaSonido(s1, s2, frecMuestreo, tiempo)
% Duracion de s1
duracion_s1 = size(s1,1)/frecMuestreo;

% Si el momento indicado es mayor que la duracion de s1
if tiempo > duracion_s1
    % Insertamos s2 al final de s1
    y = [s1;s2];
else
    % No podemos establecer el tiempo inicial en 0
    tiempo_ini = 0.001;
    
    % Obtenemos las muestras inciales y finales de cada tramo de s1
    muestra_ini1 = fix(tiempo_ini*frecMuestreo);
    muestra_fin1 = fix(tiempo*frecMuestreo);
    
    % Ademas, obtenemos los dos tramos de s1
    tramo1_s1 = s1(muestra_ini1:muestra_fin1, :);
    
    muestra_ini2 = muestra_fin1;
    muestra_fin2 = fix(duracion_s1*frecMuestreo);
    
    tramo2_s1 = s1(muestra_ini2:muestra_fin2, :);
    
    % Devolvemos s1 con s2 en medio
    y = [tramo1_s1; s2; tramo2_s1];
end
end