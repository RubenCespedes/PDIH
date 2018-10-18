% 1. Leer un fichero .WAV con wavread (no muy largo, de menos de 20 segundos de duraci�n). 
y = audioread('del1al10.wav');

% 2. Dibujar la forma de onda de los canales con dibujaSonido. 
dibujaSonido(y, 'Forma de onda');

% 3. Obtener la informaci�n de la cabecera del fichero con getCabeceraWav. 
[ch, freq, resol, numBytes] = getCabeceraWav('del1al10.wav');

% 4. Grabar un fichero de 2 segundos desde la tarjeta de sonido. 
grabacion = grabaSonido('sonido.wav', 8192, 16, 1, 2.0);
reproduceSonido(grabacion, 16000, 16);

% 5. Insertar la se�al grabada a los 3 segundos de la primera se�al. 
grabacion = grabaSonido('sonido.wav', 8192, 16, 1, 2.0);
mezcla = insertaSonido(y, grabacion, 44100, 3.0);
reproduceSonido(mezcla, 16000, 16);

% 6. Aplicar un eco del 40% con 0.5 segundos de retraso. 
ecoSignal = eco(y, 8192, 0.5, 0.8);
reproduceSonido (ecoSignal, 16000, 16);
 
% 7. Aplicar un efecto de fadeout en el �ltimo segundo. 
atenuada = fadeOut(y, 8192, 1.0);
reproduceSonido (atenuada, 16000, 16);

% 8. Dibujar la forma de onda de la se�al resultante.
dibujaSonido(atenuada, 'Forma de onda');
 
% 9. Almacenar la se�al obtenida como un fichero WAV

% 10. Reproducir al rev�s la se�al obtenida.
alreves = reverse(y);
reproduceSonido (alreves, 16000, 16);