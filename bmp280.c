/*
 * bmp280.c
 *
 *  Created on: Mar 26, 2025
 *      Author: Gülerizm
 */
#include "bmp280.h"
#include <stdio.h>

// Kalman filtre değişkenleri
static float Q = 0.1;
static float R = 1.0;
static float P = 1.0;
static float K = 0.0;
static float X = 0.0;

uint32_t BMP280_Read_Pressure(I2C_HandleTypeDef *hi2c) {
    uint8_t data[3];
    HAL_I2C_Mem_Read(hi2c, BMP280_ADDR, BMP280_PRESS_MSB, 1, data, 3, HAL_MAX_DELAY);

    uint32_t adc_P = ((uint32_t)data[0] << 12) | ((uint32_t)data[1] << 4) | (data[2] >> 4);
    return adc_P; // Ham basınç değeri döndürülüyor, kalibrasyon uygulanmalıdır
}

float KalmanFilter(float measurement) {
    P = P + Q;  // Hata kovaryansını güncelle
    K = P / (P + R);  // Kalman kazancını hesapla
    X = X + K * (measurement - X);  // Güncellenmiş tahmin değeri
    P = (1 - K) * P;  // Hata kovaryansını güncelle
    return X;
}

void Send_Pressure_UART( float pressure) {
    char buffer[50];
    int length = snprintf(buffer, sizeof(buffer), "Pressure: %.2f Pa\r\n", pressure);
    HAL_UART_Transmit(&huart1, (uint8_t*)buffer, length, HAL_MAX_DELAY);
}



