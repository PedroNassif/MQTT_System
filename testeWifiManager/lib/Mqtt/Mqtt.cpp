#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "Mqtt.h"
#include "cert.h"

//protótipo de funções
void receiveMsgCallback(char* topic, byte* payload, unsigned int length); //calbeck de envio de msg

//Mqtt Server
const char* mqtt_server = "a17zzpalppch0v-ats.iot.sa-east-1.amazonaws.com"; //EndPoint da Cloud AWS - Que roda o Broker MQTT

//variávies
uint8_t count = 0;
char msg[BUFFER_LEN];

//criação de instâncias
WiFiClientSecure espClient;
PubSubClient client(espClient);

void connectAWSCloud(){
  espClient.setCACert(AWS_CERT_CA);
  espClient.setCertificate(AWS_CERT_CRT);
  espClient.setPrivateKey(AWS_CERT_PRIVATE);

  client.setServer(mqtt_server, 8883); //conecta com o Broker
  client.setCallback(receiveMsgCallback); //cria um Message Handler
  Serial.println("Conectando ao AWS IOT");

  while (!client.connect(THINGNAME)) {
  Serial.print(".");
  delay(100);
  }

  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
  return;
  }
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
 
  Serial.println("AWS IoT Connected!");
  // client.publish(AWS_IOT_PUBLISH_TOPIC,"Hello World");
}


//Callbacks ======================================================================
void receiveMsgCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


void sendData(float temp, char* mac_Id){
    StaticJsonDocument<200> doc;
    doc["Mac_ID"] = mac_Id;
    doc["Temperatura"] = temp;

    char jsonBuffer[512];
    serializeJson(doc, jsonBuffer);

    client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void clientLoop(){
  client.loop();
}