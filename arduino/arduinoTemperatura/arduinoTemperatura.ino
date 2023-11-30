#include "DHT.h" // including the library of DHT11 #define DHTTYPE DHT11 // DHT 11 sensor usado
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#define DHTTYPE DHT11
#define dht_dpin 0 //D3
#define LED_VERDE 16 // Pin D0 en una placa ESP8266.
#define LED_ROJO 14  // Pin D5 en una placa ESP8266.
#define LED_AZUL 12  // Pin D6 en una placa ESP8266.


DHT dht(dht_dpin, DHTTYPE);
const char* ssid = "wifi";
const char* password = "password";

HTTPClient httpClient;
WiFiClient wClient;

String URL = "http://ip:3000/api/logTemp/4/";

void setup(void)
{
  dht.begin();
  Serial.begin(9600);
  Serial.println("Inicializando conexión a My SQL");
  pinMode(LED_VERDE, OUTPUT);   // Configura el pin LED_VERDE como salida.
  pinMode(LED_ROJO, OUTPUT);    // Configura el pin LED_ROJO como salida.
  pinMode(LED_AZUL, OUTPUT);    // Configura el pin LED_AZUL como salida.
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

float temperatura = dht.readTemperature();
if (isnan(temperatura)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }

Serial.print("Temperatura = ");
Serial.print(temperatura);
Serial.println(" C ");
Serial.println();
if (temperatura > 24.0) {
    parpadear(LED_ROJO);  // Llama a la función parpadear con el pin LED_ROJO si la temperatura es mayor a 27°C.
    } else if (temperatura < 15.0) {
    parpadear(LED_AZUL);  // Llama a la función parpadear con el pin LED_AZUL si la temperatura es menor a 17°C.
    } else {
    digitalWrite(LED_VERDE, HIGH);  // Enciende el LED_VERDE si la temperatura está entre 17°C y 26°C. Lo que hace digitalWrite es controlar el estado del led.
    }

  delay(3000);
  logIntento(temperatura); 
}


void parpadear(int led) {
  for (int i = 0; i < 3; i++) {  // Repite el siguiente bloque de código 3 veces por temperatura que reciba osea por cada vez que se mande a llamar.
    digitalWrite(led, HIGH);  // Enciende el LED especificado por el argumento "pin".
    delay(500);  // Espera 500 milisegundos
    digitalWrite(led, LOW);  // Apaga el LED
    delay(500);  // Espera otros 500 milisegundos
  }
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