/*
 * Flash_W25QX.h
 *
 *  Created on: Sep 11, 2021
 *      Author: anura
 */

#ifndef INC_FLASH_W25QX_H_
#define INC_FLASH_W25QX_H_

#include "stm32l4xx_hal.h"
#include "stdbool.h"

#define W25QXX_DUMMY_BYTE         0xA5

/*-----------SPI PINS AND PORTS------------------*/
#define SPI_MISO_PIN GPIO_PIN_2
#define SPI_MISO_PORT GPIOC

#define SPI_MOSI_PIN GPIO_PIN_3
#define SPI_MOSI_PORT GPIOC

#define SPI_SCK_PIN GPIO_PIN_10
#define SPI_SCK_PORT GPIOB

#define SPI_CS_PIN GPIO_PIN_8
#define SPI_CS_PORT GPIOC



extern SPI_HandleTypeDef hspi2;

uint8_t W25qxx_readStatusRegister_1(void);
uint8_t	W25qxx_Spi(uint8_t	Data);
uint32_t W25qxx_ReadID(void);
void W25qxx_EnableDataWrite(void);
void W25qxx_DisableDataWrite(void);
bool isWriteENableLatch_Set(void);
void W25qxx_EraseSector(void);
bool isBusyBit_Set(void);

void W25qxx_PageProgram(void);
#endif /* INC_FLASH_W25QX_H_ */
