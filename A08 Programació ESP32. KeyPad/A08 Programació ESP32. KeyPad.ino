#include <Keypad.h>  // Llibreria que gestiona l'escombrat de la matriu del KeyPad

// --- Configuració del KeyPad 4x4 ---
const byte ROWS = 4;
const byte COLS = 4;

// Caràcter associat a cada tecla segons la seva posició (fila, columna)
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Pins de l'ESP32 connectats a les files (R1-R4) i columnes (C1-C4)
byte rowPins[ROWS] = {19, 18, 5, 17};
byte colPins[COLS] = {16, 4, 2, 15};

// Objecte Keypad: relaciona el mapa de tecles amb els pins
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// --- LEDs d'estat ---
const int LED_VERD = 25;     // Accés concedit
const int LED_VERMELL = 26;  // Accés denegat

// --- Contrasenya i control d'intents ---
const String PASSWORD = "1234";               // Contrasenya correcta
const int MAX_LONGITUD = 8;                   // Màxim de tecles que s'accepten
const int MAX_INTENTS = 3;                    // Intents abans de bloquejar
const unsigned long TEMPS_BLOQUEIG = 10000;   // Durada del bloqueig (10 s)

String entrada = "";  // Tecles acumulades per l'usuari
int intents = 0;      // Comptador d'intents fallits

void setup() {
  Serial.begin(115200);  // Inicia el monitor sèrie
  pinMode(LED_VERD, OUTPUT);
  pinMode(LED_VERMELL, OUTPUT);
  digitalWrite(LED_VERD, LOW);     // Els LED comencen apagats
  digitalWrite(LED_VERMELL, LOW);

  Serial.println("=== Control d'accés amb KeyPad ===");
  Serial.println("Introdueix la contrasenya i prem # per confirmar.");
  Serial.println("Prem * per esborrar.");
}

void loop() {
  char tecla = keypad.getKey();    // Retorna la tecla premuda o NO_KEY
  if (tecla == NO_KEY) return;     // Si no hi ha tecla, no fa res

  if (tecla == '*') {
    // '*' esborra l'entrada actual
    entrada = "";
    Serial.println("\nEntrada esborrada.");
  }
  else if (tecla == '#') {
    // '#' confirma i valida la contrasenya
    validarContrasenya();
  }
  else if (entrada.length() < MAX_LONGITUD) {
    // Qualsevol altra tecla s'afegeix a l'entrada
    entrada += tecla;
    Serial.print('*');  // Mostra '*' per no revelar la contrasenya
  }
}

// Compara l'entrada amb la contrasenya i gestiona LED i intents
void validarContrasenya() {
  Serial.println();

  if (entrada == PASSWORD) {
    // Contrasenya correcta: LED verd 3 s i es reinicia el comptador
    Serial.println("Accés CONCEDIT");
    intents = 0;
    digitalWrite(LED_VERD, HIGH);
    delay(3000);
    digitalWrite(LED_VERD, LOW);
  } else {
    // Contrasenya incorrecta: suma un intent i encén el LED vermell 1 s
    intents++;
    Serial.print("Contrasenya INCORRECTA. Intent ");
    Serial.print(intents);
    Serial.print(" de ");
    Serial.println(MAX_INTENTS);

    digitalWrite(LED_VERMELL, HIGH);
    delay(1000);
    digitalWrite(LED_VERMELL, LOW);

    // Si s'arriba al límit d'intents, bloqueja el sistema 10 s
    if (intents >= MAX_INTENTS) {
      Serial.println("Massa intents. Sistema bloquejat 10 segons.");
      digitalWrite(LED_VERMELL, HIGH);
      delay(TEMPS_BLOQUEIG);  // Durant el delay no es llegeixen tecles
      digitalWrite(LED_VERMELL, LOW);
      intents = 0;            // Es reinicia el comptador
      Serial.println("Sistema desbloquejat.");
    }
  }
  entrada = "";  // Es neteja l'entrada per al següent intent
}