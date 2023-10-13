//Bibiliotecas
#include <Arduino.h>
#include "FS.h"
#include <LittleFS.h>
#include <WiFiManager.h>
#include "FS_Functions.h"
#include "Wifi_Functions.h"
#include "Draws.h"

//váriaveis globais
uint16_t data = 4;


void setup(){
    Serial.begin(115200, SERIAL_8N1);
    displayBegin(); //Inicia o display
    Serial.println("\nStarting");
    
    LittleFSbegins(); //Inicia o LittleFS
    WiFi.mode(WIFI_STA); //Modo Station para programar
    
    drawIniciando();
    
    char nome_da_rede[] = "Esp32-Ap"; //Define o nome da rede
    configPortal(&nome_da_rede[0]); //Envia o nome da rede

    
   
}

void loop(){
}