#include <ESP8266WiFi.h>

const char* ssid = "LUZ NELLY";      // Nombre de la red WiFi
const char* password = "21823267"; // Contraseña de la red

int ledPin1 = 0;
int ledPin2 = 2;

WiFiServer server(80);

void setup() {
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, LOW); 
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LOW); 
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  Serial.println("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConectado a WiFi!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Server started");

  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/\n");
  
}

void loop() {  
  WiFiClient client = server.available();
  
  if(!client){
    return;
  }
  
  while(!client.available()){
    delay(1);
  }
  
  String request = client.readStringUntil('\r');
  if (request.indexOf("/favicon")== -1){
    Serial.println("New client");
    Serial.println(request);  
  }
  client.flush();

  // Control del primer LED
  int value = LOW;
  if (request.indexOf("/LED1=ON") != -1){
    digitalWrite(ledPin1,HIGH);
  }
  if (request.indexOf("/LED1=OFF") != -1){
    digitalWrite(ledPin1, LOW);
  }
  
  // Control del segundo LED
  if (request.indexOf("/LED2=ON") != -1) {
    digitalWrite(ledPin2, HIGH);
  }
  if (request.indexOf("/LED2=OFF") != -1) {
    digitalWrite(ledPin2, LOW);
  }



  // Set ledPin according to the request
  //digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");



  client.println("<h1>Control de LEDs</h1>");
  client.println("<p>LED 1: <a href=\"/LED1=ON\"><button>Encender</button></a> <a href=\"/LED1=OFF\"><button>Apagar</button></a></p>");
  client.println("<p>LED 2: <a href=\"/LED2=ON\"><button>Encender</button></a> <a href=\"/LED2=OFF\"><button>Apagar</button></a></p>");

  client.println("</html>");
 
  delay(10);
  Serial.println("Client disonnected");
  Serial.println("");




}
