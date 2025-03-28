/*
 * bmp280.h
 *
 *  Created on: Mar 26, 2025
 *      Author: Gülerizm
 */

#ifndef BMP280_H
#define BMP280_H

#include "stm32f1xx_hal.h"
#include <stdint.h>

#define BMP280_ADDR (0x76 << 1)  // BMP280 I2C adresi (SDO pini GND'ye bağlıysa)
#define BMP280_PRESS_MSB 0xF7    // Basınç verisi başlangıç adresi


// UART değişkeni dışarıdan kullanılabilsin
extern UART_HandleTypeDef huart1;  // 🌟 Burada sadece bildiriyoruz, tanımlamıyoruz!

uint32_t BMP280_Read_Pressure(I2C_HandleTypeDef *hi2c);
float KalmanFilter(float measurement);
void Send_Pressure_UART(float pressure);

#endif /* INC_BMP280_H_ */
