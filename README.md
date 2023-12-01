# API-PlantGPT_IoT
Made by:  Arnulfo Iván Treviño Cavazos - Fernando Morán Fougerat - Jose Ignacio Paez Batallas - Julen Hoppenstedt Mandiola - Pedro Alejandro Rodriguez Gonzalez 

This project allows us to keep tabs on different aspects about a plants wellbeing, taking advantage of tools such as sensores and NodeMCU ESP8266, inserting the measured data to an SQL database. The sensors that we employed are: 


* Distance infrared sensor
   * We built a tank, and used HC-SR04 Ultrasonic Distance Sensor to check if the tank is empty
* Humity sensor
   * We added a humity sensor, that checks the current percentage of the plant and, if needed, turns on the water pump.
* Temperature sensor
   * This sensor returns the current temperature in °C, to see if it's okay for our plant's growth.
* Fotovoltaic resistance
   * We added a fotovoltaic resistance to see the current light it receives, and turns on a led light (in preference, turn on a LED grow bulb).
* Movement sensor
   * This PIR  sensorschecks if there is movement that affects the plant, such as wind and/or animals.
 
  ## Dashboard: https://lookerstudio.google.com/reporting/98638818-5ba9-4e56-a093-f12c14b2fe23
  <img width="960" alt="Captura de pantalla 2023-11-30 212200" src="https://github.com/fermofou/PlantGPT/assets/122712372/a18bfb16-ba39-4ad5-9ecf-d193a0943be5">

  
![WhatsApp Image 2023-11-25 at 11 47 20 PM](https://github.com/fermofou/PlantGPT/assets/122712372/dcf55b68-0082-4fc1-9566-33e77b1710d2)
