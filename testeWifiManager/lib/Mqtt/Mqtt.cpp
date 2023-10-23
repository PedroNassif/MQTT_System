#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "FS.h"
#include "FS_Functions.h"
#include "Mqtt.h"

//Mqtt Server
const char mqtt_server[] = "a17zzpalppch0v-ats.iot.sa-east-1.amazonaws.com"; //EndPoint da Cloud AWS - Que roda o Broker MQTT
const char mqtt_port[6] = "8883";

//Strings de leitura do certificado da AWS cloud
String Read_rootca;
String Read_cert;
String Read_privatekey;

//variávies
uint8_t count = 0;
char msg[BUFFER_LEN];

//criação de instâncias
WiFiClientSecure espClient;
PubSubClient client(espClient);

bool certifingAWSCloud(const char* way1, const char* way2, const char* way3){
    Read_rootca = readFile(LittleFS, way1);
    Read_cert = readFile(LittleFS, way2);
    Read_privatekey = readFile(LittleFS, way3);
  
    //Convertendo as Strings em ponteiros, pois o espClient não aceita strings
    //Aloca dinamicamente um bloco de memória do tamanho especificado em bytes usando malloc e retorna um ponteiro para o início desse bloco. 
    char* pRead_rootca;
    pRead_rootca = (char *)malloc(sizeof(char) * (Read_rootca.length() + 1));
    strcpy(pRead_rootca, Read_rootca.c_str()); //copia uma sequência de caracteres (string) para esse bloco usando strcpy.

    char* pRead_cert;
    pRead_cert = (char *)malloc(sizeof(char) * (Read_cert.length() + 1));
    strcpy(pRead_cert, Read_cert.c_str());

    char* pRead_privatekey;
    pRead_privatekey = (char *)malloc(sizeof(char) * (Read_privatekey.length() + 1));
    strcpy(pRead_privatekey, Read_privatekey.c_str());

    //Printando os ponteiros convertidos
    Serial.println("================================================================================================");
    Serial.println("Certificates that passing to espClient Method");
    Serial.println();
    Serial.println("Root CA:");
    Serial.write(pRead_rootca);
    Serial.println("================================================================================================");
    Serial.println();
    Serial.println("Cert:");
    Serial.write(pRead_cert);
    Serial.println("================================================================================================");
    Serial.println();
    Serial.println("privateKey:");
    Serial.write(pRead_privatekey);
    Serial.println("================================================================================================");

    //Passando os ponteiros pro espClient
    espClient.setCACert(pRead_rootca);
    espClient.setCertificate(pRead_cert);
    espClient.setPrivateKey(pRead_privatekey);

    return true;
}

void setMqttServer(){
  Serial.print("mqtt_server: ");
  Serial.println(mqtt_server);
  Serial.print("mqtt_port: ");
  Serial.println(mqtt_port);
  client.setServer(*mqtt_server, (int) mqtt_port);
  client.setCallback(receiveMsgCallback);
}

void connectMqttServer() {
    if(!client.connected()){
      Serial.println("Não conectado, tentando reconectar...");
        reconnect();
    } else{
        client.loop();
    }
     
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

void reconnect(){
    // Loop until we're reconnected
    while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // String clientId = "ESP32-";
    // clientId += String(random(0xffff), HEX); //Aqui ele cria um Id pro client - ele faz esse número randômico pois cada ID tem que ser único e isso reduz as chances de duplicidade

    
    if (client.connect("ESP32_TX4S")) { //Depois olhar essa função connect pois ela em algumas variadades que podem ser utilizadas
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("TX4S_Temperature","hello world");
      // ... and resubscribe
      client.subscribe("TX4S_Broker");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void sendData(float temp, char* mac_Id){
    String data = String(temp);
    snprintf(msg, BUFFER_LEN, "{\"mac_Id\": \"%s\", \"Temperature\": \"%s\"}", mac_Id, data.c_str());
    Serial.print("Publish message: ");
    Serial.print(count);
    Serial.println(msg);
    client.publish("TX4S_Temperature", msg);
    count = count + 1;
}