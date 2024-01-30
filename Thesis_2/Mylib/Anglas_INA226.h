#ifndef INA226_H
#define INA226_H

#include "stm32f1xx_hal.h"

#define INA226_I2C_ADDRESS_REF 0x40
#define INA226_I2C_ADDRESS_SEN 0x45
#define INA226_SHUNT_RESISTOR 0.01 // shunt Resistor R010

void INA226_Init(I2C_HandleTypeDef *hi2c,uint8_t INA226_I2C_ADDRESS);
float INA226_ReadShuntVoltage(I2C_HandleTypeDef *hi2c,uint8_t INA226_I2C_ADDRESS);
float INA226_ReadBusVoltage(I2C_HandleTypeDef *hi2c,uint8_t INA226_I2C_ADDRESS);
float INA226_ReadCurrent(I2C_HandleTypeDef *hi2c,uint8_t INA226_I2C_ADDRESS);
float INA226_ReadPower(I2C_HandleTypeDef *hi2c,uint8_t INA226_I2C_ADDRESS);

#endif /* INA226_H */