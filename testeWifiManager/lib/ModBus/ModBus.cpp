#include <ModbusMaster.h>
#include "ModBus.h"


//Criação de objetos 
ModbusMaster modbus;


void modbusBegin(){
modbus.begin(SLAVE_ADD, RS485Serial); // Inicializa o ModbusMaster com o endereço do escravo e a porta Serial RS485
}

//Função que vai fazer o checkup e caso houver erros, vai identificar qual!
bool getMsgError(ModbusMaster *node, uint8_t result) {
  String tmpstr2 = "\r\n";
  switch (result) {
    case node->ku8MBIllegalFunction:
      tmpstr2 += "Illegal Function";
      break;
    case node->ku8MBIllegalDataAddress:
      tmpstr2 += "Illegal Data Address";
      break;
    case node->ku8MBIllegalDataValue:
      tmpstr2 += "Illegal Data Value";
      break;
     case node-> ku8MBSlaveDeviceFailure:
       tmpstr2 += "Slave Device Failure";
       break;
    case node->ku8MBInvalidSlaveID:
      tmpstr2 += "Invalid Slave ID";
      break;
    case node->ku8MBInvalidFunction:
      tmpstr2 += "Invalid Function";
      break;
    case node->ku8MBResponseTimedOut:
      tmpstr2 += "Response Timed Out";
      break;
    case node->ku8MBInvalidCRC:
      tmpstr2 += "Invalid CRC";
      break;
    default:
      tmpstr2 += "Unknown error: " + String(result);
      break;
  }
  Serial.println(tmpstr2);
  return false;
}

uint8_t getControlerRegister(){
  uint8_t result = modbus.readInputRegisters(0x03E8, 1);
    return result;
}

bool readResultRegister(uint8_t resultRegister){
    if(resultRegister == modbus.ku8MBSuccess){
        return true;
    } return false;
}

float getTemperature(){
    float temp = modbus.getResponseBuffer(0)/10.0f;
    return temp;
}

void getError(uint8_t resultRegister){
    getMsgError(&modbus, resultRegister);
}