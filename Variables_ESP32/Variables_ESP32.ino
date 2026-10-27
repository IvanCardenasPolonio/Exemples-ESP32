// Exemples ESP32 - A05 Variables (Iván Cárdenas Polonio)

const int LED_PIN = 2;               // const: valor que NO canvia mai; GPIO 2 = LED intern
int contador = 0;                    // int: enter (4 bytes a l'ESP32); compta les voltes
long tempsEspera = 500;              // long: enter gran (4 bytes); temps del delay en ms
const long TEMPS_MAXIM = 2000;       // const long: límit màxim d'espera (no canvia)
unsigned long tempsInici = 0;        // unsigned long: enter només positiu; guarda millis()
float temperatura = 23.5;            // float: número amb decimals (4 bytes)
char inicial = 'E';                  // char: un sol caràcter (1 byte), cometes simples
bool wifiConnectat = false;          // bool: només true o false (1 byte); estat de la Wi-Fi
bool encendido = true;               // bool: controla si el LED parpelleja
String nomProjecte = "Projecte 2 IoT"; // String: cadena de text, cometes dobles

void setup() {
  pinMode(LED_PIN, OUTPUT);          // el pin del LED és una sortida
  Serial.begin(115200);              // velocitat del port sèrie (igual que el Monitor Sèrie)
  delay(1000);                       // espera 1 s perquè s'estableixi el port sèrie
  tempsInici = millis();             // guarda els ms des de l'arrencada en una variable

  Serial.println("=== Variables a l'ESP32 ===");                     // títol
  Serial.println(nomProjecte);                                       // mostra el String

  Serial.print("LED_PIN = ");          Serial.println(LED_PIN);      // valor del const int
  Serial.print("contador = ");         Serial.println(contador);     // valor de l'int
  Serial.print("tempsEspera = ");      Serial.println(tempsEspera);  // valor del long
  Serial.print("tempsInici = ");       Serial.println(tempsInici);   // valor de l'unsigned long
  Serial.print("temperatura = ");      Serial.println(temperatura);  // valor del float
  Serial.print("inicial = ");          Serial.println(inicial);      // valor del char
  Serial.print("wifiConnectat = ");    Serial.println(wifiConnectat);// bool: 0 = false, 1 = true

  Serial.println("--- Mida en bytes ---");                           // sizeof() = bytes que ocupa un tipus
  Serial.print("int: ");           Serial.println(sizeof(int));      // 4 bytes a l'ESP32 (no 2)
  Serial.print("long: ");          Serial.println(sizeof(long));     // 4 bytes
  Serial.print("unsigned long: "); Serial.println(sizeof(unsigned long)); // 4 bytes
  Serial.print("float: ");         Serial.println(sizeof(float));    // 4 bytes
  Serial.print("char: ");          Serial.println(sizeof(char));     // 1 byte
  Serial.print("bool: ");          Serial.println(sizeof(bool));     // 1 byte
}

void loop() {
  if (encendido) {                   // només treballa si l'estat és true
    contador++;                      // suma 1 (equival a contador = contador + 1)
    temperatura += 0.5;              // suma 0.5 a la temperatura simulada

    digitalWrite(LED_PIN, HIGH);     // encén el LED
    delay(tempsEspera);              // espera el temps guardat a la variable
    digitalWrite(LED_PIN, LOW);      // apaga el LED
    delay(tempsEspera);              // torna a esperar el mateix temps

    Serial.print("Volta ");          Serial.print(contador);           // número de volta
    Serial.print(" | espera: ");     Serial.print(tempsEspera);        // ms d'espera actual
    Serial.print(" ms | temp: ");    Serial.print(temperatura);        // temperatura actual
    Serial.print(" C | temps: ");    Serial.print((millis() - tempsInici) / 1000); // s des de l'inici
    Serial.println(" s");            // final de línia

    tempsEspera += 500;              // augmenta l'espera 500 ms (tempsEspera = tempsEspera + 500)

    if (tempsEspera >= TEMPS_MAXIM) {// si arriba o passa del màxim (>= i no ==, per seguretat)
      encendido = false;             // canvia l'estat a false: el LED s'atura
      Serial.println("Temps màxim assolit. LED aturat."); // avís pel Monitor Sèrie
    }
  } else {
    // encendido és false: no fem res
  }
}