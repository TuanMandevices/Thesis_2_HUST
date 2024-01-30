#include "Anglas_INA226.h"

#define INA226_CONFIG_REGISTER 0x00
#define INA226_SHUNT_VOLTAGE_REGISTER 0x01
#define INA226_BUS_VOLTAGE_REGISTER 0x02
#define INA226_POWER_REGISTER 0x03
#define INA226_CURRENT_REGISTER 0x04

void INA226_Init(I2C_HandleTypeDef *hi2c,uint8_t INA226_I2C_ADDRESS) {
  // Khởi tạo INA226 với cấu hình mặc định
  uint8_t config[2];
  config[0] = (uint8_t)(0x41 >> 8); // Byte cao của giá trị 16-bit
  config[1] = (uint8_t)0x41; // Byte thấp của giá trị 16-bit
  HAL_I2C_Mem_Write(hi2c, INA226_I2C_ADDRESS, INA226_I2C_ADDRESS << 1, I2C_MEMADD_SIZE_8BIT, config, sizeof(config), HAL_MAX_DELAY);
}

float INA226_ReadShuntVoltage(I2C_HandleTypeDef *hi2c,uint8_t INA226_I2C_ADDRESS) {
  uint16_t shunt_voltage_raw;
  HAL_I2C_Mem_Read(hi2c, (INA226_I2C_ADDRESS << 1) | 1, INA226_SHUNT_VOLTAGE_REGISTER, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&shunt_voltage_raw, sizeof(shunt_voltage_raw), HAL_MAX_DELAY);
  return (float)shunt_voltage_raw * 2.5e-6; // LSB = 2.5uV
}

float INA226_ReadBusVoltage(I2C_HandleTypeDef *hi2c,uint8_t INA226_I2C_ADDRESS) {
  uint16_t bus_voltage_raw;
  HAL_I2C_Mem_Read(hi2c, (INA226_I2C_ADDRESS << 1) | 1, INA226_BUS_VOLTAGE_REGISTER, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&bus_voltage_raw, sizeof(bus_voltage_raw), HAL_MAX_DELAY);
  return (float)bus_voltage_raw * 1.25e-3; // LSB = 1.25mV
}

float INA226_ReadCurrent(I2C_HandleTypeDef *hi2c,uint8_t INA226_I2C_ADDRESS) {
  uint16_t current_raw;
  HAL_I2C_Mem_Read(hi2c, (INA226_I2C_ADDRESS << 1) | 1, INA226_CURRENT_REGISTER, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&current_raw, sizeof(current_raw), HAL_MAX_DELAY);
  return (float)current_raw * 0.001; // LSB = 1mA
}

float INA226_ReadPower(I2C_HandleTypeDef *hi2c,uint8_t INA226_I2C_ADDRESS) {
  uint16_t power_raw;
  HAL_I2C_Mem_Read(hi2c, (INA226_I2C_ADDRESS << 1) | 1, INA226_POWER_REGISTER, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&power_raw, sizeof(power_raw), HAL_MAX_DELAY);
  return (float)power_raw * 25.0e-3; // LSB = 25mW
}