#include <Arduino.h>
#include <WiFiManager.h>
#include "Wifi_Functions.h"

//criação de objetos
WiFiManager wm;

void configPortal (char* name){
 if (!wm.startConfigPortal(name)) {
      Serial.println("Falha ao Conectar");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      ESP.restart();
      delay(5000);
    }

    //if you get here you have connected to the WiFi
    Serial.println("Conectado!");
}