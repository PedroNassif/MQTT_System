#include <Arduino.h>

#ifndef _MODBUS_H
#define _MODBUS_H
#include <ModbusMaster.h>

//Definições=====================================================
#define RS485Serial  Serial2  // Utilize a porta Serial2 para comunicação RS485 (ou outra porta disponível)
#define SLAVE_ADD    1        // Defina o endereço do escravo aqui (pode ser qualquer valor entre 1 e 247) - Definido no proprio Controlador
#define RX_PIN      16        //RX2 
#define TX_PIN      17        //TX2 



//Funções
void modbusBegin();
bool getMsgError(ModbusMaster, uint8_t);
uint8_t getControlerRegister();
bool readResultRegister(uint8_t);
float getTemperature();
void getError(uint8_t);
#endif