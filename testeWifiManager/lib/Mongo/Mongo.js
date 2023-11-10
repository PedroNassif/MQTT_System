//passos:

//1º -- conectar no broker MQTT AWS para obter as infos de temperatura
// Configurações MQTT
const mqttBroker = 'a17zzpalppch0v-ats.iot.sa-east-1.amazonaws.com';
const mqttTopic = 'esp32/pub';

//2º -- Acessar o mongo e sua database e collection

//3º -- Inserir o dado bruto na colletion 1

//4º -- refinar os dados e mandar para outra collection