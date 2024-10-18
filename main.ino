#include <Servo.h>

Servo servo1; // Primer servo
Servo servo2; // Segundo servo

#define red 13
#define green 12
#define button2 2   // Botón para mover el primer servo a 60°
#define button4 4   // Botón para mover el primer servo a 120°
#define button7 7   // Botón para mover el primer servo a 180°

unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime4 = 0;
unsigned long lastDebounceTime7 = 0;
unsigned long debounceDelay = 50;  // Tiempo para "debouncing" (50 ms)

bool lastButtonState2 = LOW;
bool lastButtonState4 = LOW;
bool lastButtonState7 = LOW;

int currentServoAngle = 82; // Para almacenar el ángulo actual del primer servo

void setup()
{
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(button2, INPUT);
  pinMode(button4, INPUT);
  pinMode(button7, INPUT);
  
  servo1.attach(3); // Primer servo en el pin 9
  servo2.attach(5); // Segundo servo en el pin 10 (puedes cambiarlo si es necesario)
  
  // Estado inicial de los servos y LEDs
  digitalWrite(green, HIGH);  // Verde encendido cuando no hay movimiento
  digitalWrite(red, LOW);     // Rojo apagado inicialmente

  moveServo1(82);
  moveSecondServo();
}

void loop()
{
  // Leer el estado actual de los botones
  int reading2 = digitalRead(button2);
  int reading4 = digitalRead(button4);
  int reading7 = digitalRead(button7);

  // Botón en pin 2 (60 grados)
  if (reading2 != lastButtonState2) {
    lastDebounceTime2 = millis();  // Reiniciar el tiempo de debounce
  }
  
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 == HIGH) {   // Si el botón en pin 2 está presionado
      moveServo1(15);         // Mover el primer servo a 60 grados
      moveSecondServo();      // Mover el segundo servo
    }
  }
  lastButtonState2 = reading2;

  // Botón en pin 4 (120 grados)
  if (reading4 != lastButtonState4) {
    lastDebounceTime4 = millis();  // Reiniciar el tiempo de debounce
  }
  
  if ((millis() - lastDebounceTime4) > debounceDelay) {
    if (reading4 == HIGH) {   // Si el botón en pin 4 está presionado
      moveServo1(82);        // Mover el primer servo a 120 grados
      moveSecondServo();      // Mover el segundo servo
    }
  }
  lastButtonState4 = reading4;

  // Botón en pin 7 (180 grados)
  if (reading7 != lastButtonState7) {
    lastDebounceTime7 = millis();  // Reiniciar el tiempo de debounce
  }
  
  if ((millis() - lastDebounceTime7) > debounceDelay) {
    if (reading7 == HIGH) {   // Si el botón en pin 7 está presionado
      moveServo1(164);        // Mover el primer servo a 180 grados
      moveSecondServo();      // Mover el segundo servo
    }
  }
  lastButtonState7 = reading7;
}

void moveServo1(int targetAngle) {
  int deltaAngle = abs(targetAngle - currentServoAngle); // Cambio de ángulo
  int moveTime = deltaAngle * 15;  // Tiempo de movimiento (aprox 17 ms por grado)
  
  // Encender LED rojo y apagar LED verde mientras el servo se mueve
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  
  servo1.write(targetAngle);       // Mover el primer servo
  delay(153);                 // Esperar a que el primer servo termine de moverse
  
  // Apagar LED rojo y encender LED verde cuando termine el movimiento
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  
  currentServoAngle = targetAngle; // Actualizar el ángulo actual del servo
}

void moveSecondServo() {
  // Encender LED rojo y apagar LED verde mientras el segundo servo se mueve
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  servo2.write(160);           // Mover el segundo servo a 200 grados
  delay(3000);                 // Esperar 3 segundos
  servo2.write(50);             // Volver a la posición inicial
  
  // Apagar LED rojo y encender LED verde cuando termine el movimiento
  digitalWrite(red, LOW);
  digitalWrite(green,HIGH);
}
