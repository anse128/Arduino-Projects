#include <ESP8266WiFi.h>
#include <Ticker.h>

const char* ssid = "LUZ NELLY";      // Nombre de la red WiFi
const char* password = "21823267"; // Contraseña de la red

#define ledPin 4 
#define fanPin 6 

WiFiServer server(80);

Ticker ledTicker;
Ticker fanTicker;

bool ledState = false;
bool fanState = false;

// Configuración de los tiempos en segundos
int ledInterval = 24 * 60 * 60;  // 24 horas
int ledDuration = 12 * 60 * 60;  // 12 horas
float fanInterval = 2.4 * 60 * 60; // 2.4 horas
int fanDuration = 3 * 60;   // 3 minutos

void toggleLed() {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    if (ledState) {
        ledTicker.once(ledDuration, toggleLed);  // Apagar después de la duración
    } else {
        ledTicker.once(ledInterval, toggleLed);  // Encender después del intervalo
    }
}

void toggleFan() {
    fanState = !fanState;
    digitalWrite(fanPin, fanState);
    if (fanState) {
        fanTicker.once(fanDuration, toggleFan);  // Apagar después de la duración
    } else {
        fanTicker.once(fanInterval, toggleFan);  // Encender después del intervalo
    }
}

void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(fanPin, OUTPUT);

    ledTicker.once(ledInterval, toggleLed);  // Primera activación del LED
    fanTicker.once(fanInterval, toggleFan);  // Primera activación del ventilador
}

void loop() {
    // Nada que hacer aquí, todo lo maneja Ticker.
}
