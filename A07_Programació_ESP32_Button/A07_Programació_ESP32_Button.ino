#define BUTTON_PIN 13       // Pin GPIO conectado al botón
#define DEBOUNCE_TIME 50    // Tiempo de rebote en milisegundos

// Variables para la lógica del debounce
int lastSteadyState = HIGH;
int lastFlickerableState = HIGH;
int currentState;
unsigned long lastDebounceTime = 0;

// Variable para el contador de pulsaciones
int pressCounter = 0;

void setup() {
  // Inicializar la comunicación serie a 9600 baudios
  Serial.begin(9600);
  
  // Configurar el pin del botón como entrada con resistencia Pull-Up interna
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

// Función en C para gestionar el botón y el debounce
bool buttonPressed() {
  currentState = digitalRead(BUTTON_PIN);

  // Si cambia el estado debido al ruido o a la pulsación
  if (currentState != lastFlickerableState) {
    lastDebounceTime = millis();
    lastFlickerableState = currentState;
  }

  // Si ha pasado el tiempo de debounce, tomamos el estado como válido
  if ((millis() - lastDebounceTime) > DEBOUNCE_TIME) {
    if (lastSteadyState != currentState) {
      lastSteadyState = currentState;
      
      // Si el estado estable es LOW (botón presionado con INPUT_PULLUP)
      if (lastSteadyState == LOW) {
        return true; // Se detecta una pulsación válida
      }
    }
  }
  return false;
}

void loop() {
  // Llamamos a la función del botón
  if (buttonPressed()) {
    pressCounter++; // Incrementamos el contador
    Serial.print("Botó premut! Nombre de cops: ");
    Serial.println(pressCounter);
  }
}
