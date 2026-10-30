/*
  Project: Blink configurable
  Description: Hace parpadear un LED conectado al pin 23 con
               tiempos de encendido y apagado configurables.
*/

// Pin donde está conectado el LED (no cambia nunca -> const)
const int LED_PIN = 23;

// Tiempos configurables (en milisegundos)
unsigned long tempsEncès = 500;   // Tiempo con el LED encendido
unsigned long tempsApagat = 1500; // Tiempo con el LED apagado

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);  // Enciende el LED
  delay(tempsEncès);

  digitalWrite(LED_PIN, LOW);   // Apaga el LED
  delay(tempsApagat);
}