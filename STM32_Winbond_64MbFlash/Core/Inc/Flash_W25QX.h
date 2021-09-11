/*
 * Flash_W25QX.h
 *
 *  Created on: Sep 11, 2021
 *      Author: anura
 */

#ifndef INC_FLASH_W25QX_H_
#define INC_FLASH_W25QX_H_

#include "stm32l4xx_hal.h"

#define W25QXX_DUMMY_BYTE         0xA5

extern SPI_HandleTypeDef hspi2;

uint8_t	W25qxx_Spi(uint8_t	Data);

#endif /* INC_FLASH_W25QX_H_ */