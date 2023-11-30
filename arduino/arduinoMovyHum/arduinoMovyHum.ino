//CONFIGURANDO EL INTERNET Y LA CONECCION A LA BASE DE DATOS
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "wifi";
const char* password = "password";

HTTPClient httpClient;
WiFiClient wClient;

String URL = "http://ip:3000/api/logHumid/5/"; //aqui pongan su ip y su route de post (logTemp, logLuz , esta en su controller)
String URL2 = "http://ip:3000/api/logMov/1/";

//CONFIGURANDO LOS PINES
const int sensorPin = A0; // Pin donde está conectado el sensor de humedad
const int relayPin = 5;   // GPIO 5 (D1 en NodeMCU) para el relé
const int ledPin = 12;
const int inputPin = 16;

void setup() {
  //CONFIGURANDO LOS PINES
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT); // Configura el pin del relé como salida
  digitalWrite(relayPin, HIGH); // Asegura que la bomba esté apagada al inicio
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);

  //CONECCION A INTERNET
  Serial.println("**Inicializando conexión a My SQL**");
 
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  WiFi.begin(ssid, password);
  Serial.print("Conectando a red WiFi \"");
  Serial.print(ssid);
  Serial.print("\"");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConectado! IP: ");
  Serial.println(WiFi.localIP());
  delay(500);
}

void loop() {
  int res=0;
  int val = digitalRead(inputPin);
  int valor = analogRead(sensorPin); // Lee el valor del sensor
  // Convierte el valor leído a porcentaje de humedad
  float humedad = map(valor, 1023, 0, 0, 100); 
  
  // Imprime el valor de humedad en el Monitor Serial
  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.println("%");

  if (isnan(humedad)) {
    Serial.println("Error obteniendo los datos del sensor de humedad");
    return;
  }

  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("hay movimiento");
    int res=1;
    logIntento2(res);
    Serial.println(res);
  } else {
    int res=0;
    Serial.println("no hay movimiento");
    digitalWrite(ledPin, LOW); 
    Serial.println(res);
    logIntento2(res);
  }
  delay(2000); //espero 2 segundos

  // Enciende la bomba si la humedad es menor al 10%
  if (humedad < 24) {
    digitalWrite(relayPin, LOW); // Enciende la bomba
    delay(3000); // Espera 3 segundo antes de apagar,
    digitalWrite(relayPin, HIGH); //apago la bomba
  } 
  logIntento(humedad); //internet
   //internet
  delay(1000);
}

void logIntento(float t){
  if(WiFi.status() == WL_CONNECTED){
    String data = URL;
    data = data + t;
    Serial.println(data);
    httpClient.begin(wClient, data.c_str());
    httpClient.addHeader("Content-Type", "Content-Type: application/json");
    int httpResponseCode = httpClient.POST(data.c_str());
    Serial.println(httpResponseCode);
    httpClient.end();
  }

  return;
}

void logIntento2(float t){
  if(WiFi.status() == WL_CONNECTED){
    String data = URL2;
    data = data + t;
    Serial.println(data);
    httpClient.begin(wClient, data.c_str());
    httpClient.addHeader("Content-Type", "Content-Type: application/json");
    int httpResponseCode = httpClient.POST(data.c_str());
    Serial.println(httpResponseCode);
    httpClient.end();
  }

  return;
}