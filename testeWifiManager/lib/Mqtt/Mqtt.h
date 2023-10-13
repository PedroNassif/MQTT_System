//Biblioteca MQTT 
#include <Arduino.h>
#include <WiFiClientSecure.h>

#ifndef _MQTT_SERVER_H
#define _MQTT_SERVER_H

//Mqtt Server
const char* mqtt_server;
char mqtt_port[6];

//Strings de leitura do certificado da AWS cloud
String Read_rootca;
String Read_cert;
String Read_privatekey;

WiFiClientSecure espClient;
PubSubClient client(espClient);


#endif