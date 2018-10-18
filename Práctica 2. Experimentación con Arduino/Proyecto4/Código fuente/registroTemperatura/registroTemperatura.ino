#include <EEPROM.h>

// Variables
// Guarda la lecuta actual del puerto serie
char input;
// Almacena el numero de datos introducidos en la EEPROM
int n_datos = 0;
// Almacena la direccion del EEPROM
int eeAddress = 0;
// Pin analogico del sensor
int pinSensor = A0;
// Almacenar datos en la EEPROM
float f = 0.00f;
float temperatura = 0;
int valor;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Realizamos la lectura del puerto serie
  input = Serial.read();

  switch(input){
    case 'r':
      for(int i=0; i < n_datos; i++){
        eeAddress = i*sizeof(float);
        EEPROM.get(eeAddress, f);
        Serial.print("Lectura ");
        Serial.print(i);
        Serial.print(":");
        Serial.println(f,3);
      }

      break;
    case 'w':
      eeAddress = n_datos*sizeof(float);

      valor = analogRead(A0);
      temperatura = (((valor*5.0)/1023)-0.5)/0.01;

      if(n_datos < 128){
        // Introducimos la temperatura actual en la EEPROM
        EEPROM.put(eeAddress, temperatura);
        // Aumentamos el numero de datos
        n_datos++;
      }

      break;
    case 'b':
      for(int i=0; i < EEPROM.length(); i++){
        EEPROM.write(i, 0); 
      }

      n_datos = 0;
  }

}
