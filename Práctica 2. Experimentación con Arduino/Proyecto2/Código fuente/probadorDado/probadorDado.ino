// Variables. Array con los pines de cada uno de los LEDs.
int pines[7] = {4,5,6,7,8,9,10};

void setup() {
  Serial.begin(9600);

  // Establecemos todos los pines como salidas
  for(int i=0; i < 7; i++){
    pinMode(pines[i], OUTPUT);
  }

  // Basamos la semilla en la lectura analogica del pin 0 (desconectado) para que en la ejecucion de cada sketch la semilla sea distinta
  randomSeed(analogRead(0));
}

void loop() {
  // Realizamos 200 tiradas
  for(int i = 0; i < 200; i++){
    tirada();
    delay(1000);
  }

  delay(30000000);
}

void tirada(){
  // Almacena el valor del dado obtenido
  int n = 0;
  
  for(int i=0; i < 5; i++){
    // Creamos un numero aleatorio
    n = createRandom();
    // Encendemos el numero obtenido con los LEDs correspondiente
    onNumber(n);
    delay(300);
  }

  // Mandamos el numero
  Serial.println(n);
}

int createRandom(){
  // Creamos un random entre 1 y 6
  int randNumber = random(1,7);

  return randNumber;
}

void onNumber(int number){
  // Reiniciamos todos los LEDs para mostrar el numero que corresponda
  for(int i=0; i < 7; i++){
    digitalWrite(pines[i], LOW);
  }

  // Dependiendo del numero obtenido encendemos unos LEDs u otros
  switch(number){
    case 1:
      // encender pin 4
      digitalWrite(pines[0], HIGH);
      break;
    case 2:
      // encender pin 5 y 10
      digitalWrite(pines[1], HIGH);
      digitalWrite(pines[6], HIGH);
      break;
    case 3:
      // Encender pines 4, 5 y 10
      digitalWrite(pines[0], HIGH);
      digitalWrite(pines[1], HIGH);
      digitalWrite(pines[6], HIGH);
      break;
    case 4:
      // Encender pines 5, 7, 8 y 10
      digitalWrite(pines[1], HIGH);
      digitalWrite(pines[3], HIGH);
      digitalWrite(pines[4], HIGH);
      digitalWrite(pines[6], HIGH);
      break;
    case 5:
      // Encender pines 4, 5, 7, 8 y 10
      digitalWrite(pines[0], HIGH);
      digitalWrite(pines[1], HIGH);
      digitalWrite(pines[3], HIGH);
      digitalWrite(pines[4], HIGH);
      digitalWrite(pines[6], HIGH);
      break;
    case 6:
      // Encender pines 5, 6, 7, 8, 9 y 10
      digitalWrite(pines[1], HIGH);
      digitalWrite(pines[2], HIGH);
      digitalWrite(pines[3], HIGH);
      digitalWrite(pines[4], HIGH);
      digitalWrite(pines[5], HIGH);
      digitalWrite(pines[6], HIGH);
      break;
  }
}

