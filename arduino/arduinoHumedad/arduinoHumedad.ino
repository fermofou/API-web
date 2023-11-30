#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>


const char* ssid = "wifi";
const char* password = "password";




HTTPClient httpClient;
WiFiClient wClient;


String URL = "http://ip:3000/api/logHumid/5/"; //aqui pongan su ip y su route de post (logTemp, logLuz , esta en su controller)
 
 //Selecciono pines
const int sensorPin = A0;


void setup() {
  Serial.begin(9600);
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
  int valor = analogRead(sensorPin);  // Leemos el valor del sensor


  // Convertimos el valor leído a porcentaje de humedad
  float humedad = map(valor, 1023, 0, 0, 100);  // El valor se invierte ya que 0 es máximo humedad y 1023 es mínimo humedad
 
  // Imprimimos el valor de humedad en el Monitor Serial
  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.println("%");


    if (isnan(humedad)) {
      Serial.println("Error obteniendo los datos del sensor de humedad");
      return;
    }
   
    logIntento(humedad); //internet
    delay(10000); //cada 10 segundos
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
