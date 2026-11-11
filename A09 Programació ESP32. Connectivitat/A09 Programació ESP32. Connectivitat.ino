#include <WiFi.h>
#include <time.h>


const char* NTP_SERVER = "es.pool.ntp.org";
const char* TIMEZONE = "CET-1CEST,M3.5.0,M10.5.0/3";


const char* DIES[] = {"Diumenge", "Dilluns", "Dimarts", "Dimecres",
                      "Dijous", "Divendres", "Dissabte"};


void setup() {
  Serial.begin(115200);


  Serial.print("Connectant al WiFi");
  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connectat. IP: ");
  Serial.println(WiFi.localIP());


  configTzTime(TIMEZONE, NTP_SERVER);
}


void loop() {
  struct tm hora;
  if (!getLocalTime(&hora)) {
    Serial.println("Esperant resposta NTP...");
    delay(1000);
    return;
  }


  char text[30];
  strftime(text, sizeof(text), "%d/%m/%Y %H:%M:%S", &hora);
  Serial.print(DIES[hora.tm_wday]);
  Serial.print(" ");
  Serial.println(text);


  delay(1000);
}