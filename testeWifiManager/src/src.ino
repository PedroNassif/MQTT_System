//Bibiliotecas
#include <Arduino.h>
#include "FS.h"
#include <LittleFS.h>
#include <WiFiManager.h>
#include "FS_Functions.h"
#include "Wifi_Functions.h"
#include "Draws.h"
#include "Mqtt.h"
#include "ModBus.h"

//váriaveis globais
const char* topicMqtt = "TX4S_Temperature";
const uint16_t dataTimeInterval = 1000;
char* esp_mac_Id;

void setup(){
    Serial.begin(115200, SERIAL_8N1); //Inicia a Serial
    modbusBegin(); //Inicia o Protocolo ModBus
    displayBegin(); //Inicia o display
    LittleFSbegins(); //Inicia o LittleFS
    WiFi.mode(WIFI_STA); //Modo Station para programar
    drawIniciando();
    
    char nome_da_rede[] = "Esp32-Ap"; //Define o nome da rede
    configPortal(&nome_da_rede[0]); //Envia o nome da rede

   if(certifingAWSCloud("/AmazonRootCA1.pem", "/certificate.pem.crt", "/private.pem.key") == true){;//Certificando o broker
    setMqttServer();
    esp_mac_Id = getMacAdress();
   }
   else{
    Serial.println("Erro no processo de certificação!");
   }
}

void loop(){
    connectMqttServer(); //Conecta ao Servidor Mqtt

    //Variáveis
    static uint32_t prevMillis = 0;
    uint8_t resultRegister = 0;
    float temp;

    if(millis() - prevMillis >= dataTimeInterval){
        prevMillis = millis();
        resultRegister = getControlerRegister();
        
        if(readResultRegister(resultRegister) == true){
            temp = getTemperature();
            drawTemp(temp);
            sendData(temp, esp_mac_Id);

        }
        else{
            getError(resultRegister);
            drawErro();
        } 
    }
}