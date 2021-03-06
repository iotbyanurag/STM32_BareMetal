/*
 * Flash_W25QX.c
 *
 *  Created on: Sep 11, 2021
 *      Author: anura
 */

#include "Flash_W25QX.h"



uint8_t	W25qxx_Spi(uint8_t	Data)
{
	uint8_t	ret;
	HAL_SPI_TransmitReceive(&hspi2,&Data,&ret,1,100);
	return ret;
}

uint32_t W25qxx_ReadID(void)
{
  uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;
  HAL_GPIO_WritePin(SPI_CS_PORT,SPI_CS_PIN,GPIO_PIN_RESET);
  W25qxx_Spi(0x9F);
  Temp0 = W25qxx_Spi(W25QXX_DUMMY_BYTE);
  Temp1 = W25qxx_Spi(W25QXX_DUMMY_BYTE);
  Temp2 = W25qxx_Spi(W25QXX_DUMMY_BYTE);
  HAL_GPIO_WritePin(SPI_CS_PORT,SPI_CS_PIN,GPIO_PIN_SET);
  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
  return Temp;
}

// READ status register 1  - 0x05


uint8_t W25qxx_readStatusRegister_1(void){
	uint8_t staus_byte;
	HAL_GPIO_WritePin(SPI_CS_PORT,SPI_CS_PIN,GPIO_PIN_RESET);
	 W25qxx_Spi(0x05);

	staus_byte = W25qxx_Spi(W25QXX_DUMMY_BYTE);
	HAL_GPIO_WritePin(SPI_CS_PORT,SPI_CS_PIN,GPIO_PIN_SET);

	return staus_byte;

}

void W25qxx_EnableDataWrite(void){
	uint8_t staus_byte;
	// bring CS LOW
	HAL_GPIO_WritePin(SPI_CS_PORT,SPI_CS_PIN,GPIO_PIN_RESET);
	// send the command to write Status Register
	W25qxx_Spi(0x06);
	// send the data to be written
	//W25qxx_Spi(0x02);

//	staus_byte = W25qxx_Spi(W25QXX_DUMMY_BYTE);
	HAL_GPIO_WritePin(SPI_CS_PORT,SPI_CS_PIN,GPIO_PIN_SET);

}

void W25qxx_DisableDataWrite(void){
	uint8_t staus_byte;
	// bring CS LOW
	HAL_GPIO_WritePin(SPI_CS_PORT,SPI_CS_PIN,GPIO_PIN_RESET);
	// send the command to write Status Register
	W25qxx_Spi(0x04);
	// send the data to be written
	//W25qxx_Spi(0x02);

//	staus_byte = W25qxx_Spi(W25QXX_DUMMY_BYTE);
	HAL_GPIO_WritePin(SPI_CS_PORT,SPI_CS_PIN,GPIO_PIN_SET);

}

// PAGE PROGRAM - FLASH
//  First set the WEL bit in the status register-1.
// Then send the command  = 0x02
// alongwith the 24-bit address where data needs to be written
// then the actual data that needs to be written.

void W25qxx_PageProgram(void){

		uint8_t sector0[3]={0x00,0x00,0x00};
		uint8_t data[4]={0xDE,0xAD,0xDE,0xAF};

		HAL_GPIO_WritePin(SPI_CS_PORT,SPI_CS_PIN,GPIO_PIN_RESET);

		W25qxx_Spi(0x02);

		W25qxx_Spi(0x00);
		W25qxx_Spi(0xFF);
		W25qxx_Spi(0x00);

//		for(int i=0;i<4;i++){
//			W25qxx_Spi(data[i]);
//		}

		W25qxx_Spi(0xDE);
		W25qxx_Spi(0xAD);
		W25qxx_Spi(0xDE);
		W25qxx_Spi(0xAF);

		HAL_GPIO_WritePin(SPI_CS_PORT,SPI_CS_PIN,GPIO_PIN_SET);


}

// This function returns the status of the WEL bit in the FLASH status register 1.
// The page can be written only after this bit is set.

bool isWriteENableLatch_Set(void){

	bool WEL_status =0;

	WEL_status = W25qxx_readStatusRegister_1();
	WEL_status = WEL_status & 0x01;

	return WEL_status;
}


bool isBusyBit_Set(void){

	bool WEL_status =0;

	WEL_status = W25qxx_readStatusRegister_1();
	WEL_status &= (1<<1);

	return WEL_status;
}


void W25qxx_EraseSector(void){

	uint8_t sector0[3]={0x00,0x00,0x00};

	HAL_GPIO_WritePin(SPI_CS_PORT,SPI_CS_PIN,GPIO_PIN_RESET);

	W25qxx_Spi(0x20);

	W25qxx_Spi(0x00);
	W25qxx_Spi(0xFF);
	W25qxx_Spi(0x00);
	HAL_GPIO_WritePin(SPI_CS_PORT,SPI_CS_PIN,GPIO_PIN_SET);

}

uint32_t W25qxx_ReadData(void){
	uint8_t sector0[3]={0x00,0x00,0x00};
	HAL_GPIO_WritePin(SPI_CS_PORT,SPI_CS_PIN,GPIO_PIN_RESET);
	W25qxx_Spi(0x03);

	W25qxx_Spi(0x00);
	W25qxx_Spi(0xFF);
	W25qxx_Spi(0x00);
	  uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0, Temp3=0;
	  Temp0 = W25qxx_Spi(W25QXX_DUMMY_BYTE);
	    Temp1 = W25qxx_Spi(W25QXX_DUMMY_BYTE);
	    Temp2 = W25qxx_Spi(W25QXX_DUMMY_BYTE);
	    Temp3 = W25qxx_Spi(W25QXX_DUMMY_BYTE);
	    HAL_GPIO_WritePin(SPI_CS_PORT,SPI_CS_PIN,GPIO_PIN_SET);
	    Temp = (Temp0 << 24) | (Temp1 << 16) | (Temp2<<8) | Temp3;
	    return Temp;
}


