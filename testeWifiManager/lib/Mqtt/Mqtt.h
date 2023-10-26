//Biblioteca MQTT 
#include <Arduino.h>


#ifndef _MQTT_SERVER_H
#define _MQTT_SERVER_H

#define THINGNAME "ESP32_TX4S" 
#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"
#define BUFFER_LEN 2


void connectAWSCloud();
void clientLoop();
void sendData(float temp, char* mac_Id);

#endif