//Biblioteca MQTT 
#include <Arduino.h>


#ifndef _MQTT_SERVER_H
#define _MQTT_SERVER_H

#define THINGNAME "ESP32_TX4S" 
#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"
#define BUFFER_LEN 2


bool certifingAWSCloud(const char* way1, const char* way2, const char* way3);
void setMqttServer(); //seta o client - parametros defindos na biblioteca
void receiveMsgCallback(char* topic, byte* payload, unsigned int length); //calbeck de envio de msg
void connectMqttServer(); //tenta Reconexão com o client
void reconnect();
void sendData(float temp, char* mac_Id);

#endif