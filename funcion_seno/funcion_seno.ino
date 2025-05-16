
#define LED_PIN 2  // GPIO2 en ESP8266

void setup() {
  pinMode(LED_PIN, OUTPUT);
  analogWriteFreq(1000);  // Establece la frecuencia a 1 kHz
  Serial.begin(9600);
}

void loop() {
  static float t = 0;
  int pwmValue = 100;//(sin(t) * 512) + 512;  // Genera valores entre 0 y 1023

  Serial.println("Holaa");
  Serial.println(pwmValue);
  analogWrite(LED_PIN, pwmValue);
  t += 0.1;  // Ajusta la velocidad de la onda
  //delay(5);
}
