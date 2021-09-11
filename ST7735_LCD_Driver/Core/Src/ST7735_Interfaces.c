/*
 * ST7735_Interfaces.c
 *
 *  Created on: Sep 5, 2021
 *      Author: anura
 */
#include "ST7735_Interfaces.h"


void LCD_Init(){
	HAL_GPIO_WritePin(GPIOB, CS_PIN, GPIO_PIN_SET);

}

void LCD_SetMode(){

}
