#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>




#define trigPin 12
#define echoPin 14
#define LEDPin 13 // luz LED de actuador
#define SOUND_VELOCITY 0.034 //define sound velocity in cm/uS


const char* ssid = "wifi-name";
const char* password = "wifi-password";


HTTPClient httpClient;
WiFiClient wClient;


String URL = "http://ip:3000/api/logDistancia/2/"; //en Postman funciona bien manualmente ya


long duration;  //declaro variables
float distancia;
int maximumRange = 12; // maxima distancia, despues de aqui ocupamos rellenar bote
int minimumRange = 3; // Minimum distancia para evitar que se moje sensor


void setup() {
  Serial.begin(9600);
  Serial.println("***Inicializando conexión a My SQL***");
 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(LEDPin, OUTPUT); // preparo la luz led como output


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
    // float t = dht.readTemperature();
    // pone en baja trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // pongo trigPin en Alto por 10 microsegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); //pongo en bajo trigPin
  duration = pulseIn(echoPin, HIGH);   // lee echoPin, regresa el tiempo de distancia en microsegundos


  //distanceCm = duration * SOUND_VELOCITY/2; funcion pasada
  distancia=duration/58.3; //esto saca distancia en cm
  Serial.print("Distance (cm): ");   //
  Serial.println(distancia); //imprimo valor


    if (isnan(distancia)) {
      Serial.println("Error obteniendo los datos del sensor de distancia");
      return;
    }


    Serial.print("\nDistancia: ");
    Serial.print(distancia);
    Serial.print(" cm ");


    logIntento(distancia);
    if (distancia >= maximumRange || distancia <= minimumRange){
    // si esta aqui, o hay mucha distancia o el sensor se moja. prendo luz y mando mensaje
    Serial.println("Checar agua!");
    digitalWrite(LEDPin, LOW);
    }
    else {


    digitalWrite(LEDPin, HIGH); //se apaga la luz, sigue midiendo
    }  
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
