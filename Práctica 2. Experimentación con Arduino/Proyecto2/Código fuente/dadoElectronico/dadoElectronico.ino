// Indica si se ha pulsado el boton. LOW es no pulsado, HIGH es pulsado
volatile byte push = LOW;
// Pines donde estan conectados los LEDs
int pines[7] = {4,5,6,7,8,9,10};
// Pin del boton
int pinButton = 3;

void setup() {
  Serial.begin(9600);

  // Los pines de los LEDs seran de salida
  for(int i=0; i < 7; i++){
    pinMode(pines[i], OUTPUT);
  }

  // Preparamos la interrupcion para el boton. Cada vez que se pulse se cambia la variable push
  pinMode(pinButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinButton), changePush, RISING);
}

void loop() {
  delay(3000);

  // Si hemos pulsado el boton realizamos una tirada
  if(push){
    tirada();
    // Una vez realizada la tirada, cambiamos la variable push para que no se vuelva a tirar hasta que volvamos a pulsarlo
    changePush();
  }

}

void tirada(){
  // Guarda el valor obtenido
  int n = 0;
  
  for(int i=0; i < 5; i++){
    // Creamos un random entre 1 y 6
    n = createRandom();
    // Mostramos el numero con los LEDs
    onNumber(n);
    delay(300);
  }

  // Mandamos el numero al monitor serie
  Serial.println(n);
}

int createRandom(){
  // Creamos un random entre 1 y 6
  int randNumber = random(1,7);

  return randNumber;
}

void onNumber(int number){
  // Reiniciamos todos los LEDs y encendemos los correspondientes al numero obtenido
  for(int i=0; i < 7; i++){
    digitalWrite(pines[i], LOW);
  }

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

void changePush(){
  push = !push;
}

