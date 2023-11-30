#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "wifi";
const char* password = "password";


HTTPClient httpClient;
WiFiClient wClient;

String URL = "http://ip:3000/api/logLuz/3/"; //aqui pongan su ip y su route de post (logTemp, logLuz , esta en su controller)

const int ldrPin=A0;
const int led =5;
int threshold=100;

void setup()
{
  Serial.begin (9600) ; 
  pinMode(ldrPin, INPUT);
  pinMode(led,OUTPUT);

  Serial.println("Inicializando conexión a My SQL");
 
  
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

void loop() 
{
  int rawData=analogRead(ldrPin); 
  Serial.println(rawData); 
  if(rawData<25)
  {
    digitalWrite(led,HIGH);
  }
  else 
  {
    digitalWrite(led,LOW);
  }

  logIntento(rawData); 
  delay (10000);
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

