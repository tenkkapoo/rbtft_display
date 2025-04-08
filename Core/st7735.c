/*
 * st7735.c
 *
 *  Created on: Apr 6, 2025
 *      Author: Joosu
 */
#include "stm32f4xx_hal.h"

// Define your reset, data/command and chips elect pin
#define GPIO_pin_reset GPIO_PIN_1
#define GPIOx_reset GPIOA

#define GPIO_pin_dc GPIO_PIN_0
#define GPIOx_dc GPIOA

#define GPIO_pin_CS GPIO_PIN_2
#define GPIOx_CS GPIOA





void reset_display(void) {
	HAL_GPIO_WritePin(GPIOx_reset, GPIO_pin_reset, 0);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOx_reset, GPIO_pin_reset, 1);
}

void send_command(SPI_HandleTypeDef *hspi, uint8_t cmd) {
	HAL_GPIO_WritePin(GPIOx_dc, GPIO_pin_dc, 0);
	HAL_GPIO_WritePin(GPIOx_CS, GPIO_pin_CS, 0);
	HAL_SPI_Transmit(hspi, &cmd, sizeof(cmd), 100);
	HAL_GPIO_WritePin(GPIOx_CS, GPIO_pin_CS, 1);
}

void send_data(SPI_HandleTypeDef *hspi, uint8_t data) {
	HAL_GPIO_WritePin(GPIOx_dc, GPIO_pin_dc, 1);
	HAL_GPIO_WritePin(GPIOx_CS, GPIO_pin_CS, 0);
	HAL_SPI_Transmit(hspi, &data, sizeof(data), 100);
	HAL_GPIO_WritePin(GPIOx_CS, GPIO_pin_CS, 1);

}

void init_display(SPI_HandleTypeDef *hspi) {
	uint8_t sleep_on = 0x11;
	uint8_t display_on = 0x29;
	uint8_t col_mod = 0x3A;
	reset_display();
	HAL_Delay(120);
	send_command(hspi, sleep_on); //sleep out
	HAL_Delay(120);
	send_command(hspi, display_on); // display on
	HAL_Delay(120);
	send_command(hspi, col_mod); // color mod
	HAL_Delay(120);
	send_data(hspi, 0x05); // set color mod as 5-6-5
}




