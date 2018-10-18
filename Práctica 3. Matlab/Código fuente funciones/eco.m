% Produce un efecto de eco con el retraso y el factor de potencia que se
% pasen como parametros
function [y] = eco(signal, frecMuestreo, retraso, potencia)
    % Calculamos el numero de muestras necesarias para el retraso
    muestras_retraso = fix(frecMuestreo*retraso);
    
    % Si tenemos 2 canales
    if size(signal,2) == 2
        %Generamos una matriz con tantos 0 como muestras de retraso
        matrix_ceros_retraso = zeros(muestras_retraso,2);
        %Concatenamos signal con retraso_matrix
        senial_eco = [matrix_ceros_retraso;(signal*potencia)];
        %Concatenamos retraso_matrix con signal
        senial_original = [signal;matrix_ceros_retraso];
    % Tenemos l canal
    else
        matrix_ceros_retraso = zeros(muestras_retraso,1);
        senial_eco = [matrix_ceros_retraso;(signal*potencia)];
        senial_original = [signal;matrix_ceros_retraso];      
    end
    
    %Sumamos la señal original con la señal con retraso y la devolvemos
    y = senial_original + senial_eco;
end