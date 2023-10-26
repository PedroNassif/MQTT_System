//Bibiliotecas
#include <Arduino.h>
#include <WiFiManager.h>
#include "FS_Functions.h"
#include "Wifi_Functions.h"
#include "Draws.h"
#include "Mqtt.h"
#include "ModBus.h"

//Criação de objetos 
// ModbusMaster modbus;

//váriaveis globais
const char* topicMqtt = "TX4S_Temperature";
const uint16_t dataTimeInterval = 1000;
char* esp_mac_Id;

void setup(){
    Serial.begin(115200, SERIAL_8N1);       //Inicia a Serial
    modbusBegin();                          //Inicia o Protocolo Modbus RS485
    displayBegin();                         //Inicia o display
    WiFi.mode(WIFI_STA);                    //Modo Station para programar
    drawIniciando();        
    configPortal();                         //faz a configuração do portal
    connectAWSCloud();                      //Conecta no Brokwr MQTT
    esp_mac_Id = getMacAdress();            //Pega o endereço MAC do dispositivo
}

void loop(){
    clientLoop();

    //Variáveis
        static uint32_t prevMillis = 0;
        uint8_t resultRegister = 0;
        float temp;

    if(millis() - prevMillis >= dataTimeInterval){
        prevMillis = millis();
        uint8_t res = getControlerRegister();
        
        if(readResultRegister(res) == true){
            temp = getTemperature();
            drawTemp(temp);
            sendData(temp, esp_mac_Id);

        }
        else{
            getError(res);
            drawErro();
        } 
    }
}