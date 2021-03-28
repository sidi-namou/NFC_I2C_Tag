/*
 * nfcI2CTag.c
 *
 *  Created on: 28 mars 2021
 *      Author: Sidi NAMOU
 *      mail: sidi.namou1996@gmail.com
 */

#include "nfcI2CTag.h"
//#include "stm32l4xx_hal.h"



void write_To_NFC(uint8_t MemAddr, uint8_t * data, uint8_t nfc_add){


uint8_t dataToSend[17];

		dataToSend[0] = MemAddr;
		for(int i=1; i < 17; i++)dataToSend[i] = data[i-1];

		if(HAL_I2C_Master_Transmit(&hi2c2, nfc_add, dataToSend, 17, 100)!=HAL_OK)

		  HAL_UART_Transmit(&huart2,"Transmission Failed\r\n",20,20);	/*This is For debugging*/


}


void read_From_NFC(uint8_t MemAddr, uint8_t * buffer, uint8_t nfc_add){

	uint8_t data = MemAddr;


	  if(HAL_I2C_Master_Transmit(&hi2c2, nfc_add, &data, 1,
	  	                                            6)!=HAL_OK)
		  HAL_UART_Transmit(&huart2,"Transmission Failed\r\n",20,20);/*This is For debugging*/

	  if( HAL_I2C_Master_Receive(&hi2c2, nfc_add, buffer, 16,
	 	                                           100)!=HAL_OK)
	 	  HAL_UART_Transmit(&huart2,"Receiver Failed\r\n",20,20);	/*This is For debugging*/


}



void change_Slave_Address_To_Recommended_address(){

	uint8_t data[16]={};	/* Initialise all value to 0*/


	/* See if device is ready */
	if(HAL_I2C_IsDeviceReady(&hi2c2, nfc_Address, 1, 100)== HAL_OK){

		/* read first byte */
		read_From_NFC(0,data,nfc_Address);

		/* Wait for 100ms */
		HAL_Delay(100);

		/* write data read from first byte to NFC in order to change slave address to 0X04*/
		write_To_NFC(0,data,nfc_Address);

		/* Wait for 100ms */
		HAL_Delay(100);

		/* See if device slave is changed or not */
		if(HAL_I2C_IsDeviceReady(&hi2c2, nfc_address_recommended, 1, 100)!= HAL_OK)
			HAL_UART_Transmit(&huart2,"Couldn't change memory address\r\n",20,20);	/*This is For debugging*/
		else {
			/* This to check if address has changed or not */
			read_From_NFC(0,data,nfc_address_recommended);
			HAL_UART_Transmit(&huart2,data,16,20);	/*This is For debugging*/


			 }

		}




}


void change_PWD(){

	uint8_t data[16]={};

	/* read block 0x39 */
	if(HAL_I2C_IsDeviceReady(&hi2c2, nfc_address_recommended, 1, 100)== HAL_OK)
			read_From_NFC(0x39,data,nfc_address_recommended);
	else
			read_From_NFC(0x39,data,nfc_Address);

	/* Wait for 100ms */
	HAL_Delay(100);


	data[4] = (uint8_t)(PWD_AUTH >> 3*8);
	data[5] = (uint8_t)(PWD_AUTH >> 2*8);
	data[6] = (uint8_t)(PWD_AUTH >> 1*8);
	data[7] = (uint8_t)(PWD_AUTH >> 0*8);


	if(HAL_I2C_IsDeviceReady(&hi2c2, nfc_address_recommended, 1, 100)== HAL_OK)
		write_To_NFC(0x39,data,nfc_address_recommended);
	else
		write_To_NFC(0x39,data,nfc_Address);





}


void autentification_Area(uint8_t startAddress){

	uint8_t data[16];

	/* read block 0x38 */

	if(HAL_I2C_IsDeviceReady(&hi2c2, nfc_address_recommended, 1, 100)== HAL_OK)
		read_From_NFC(0x38,data,nfc_address_recommended);
		else
			read_From_NFC(0x38,data,nfc_Address);


	/* Wait for 100ms */
	HAL_Delay(100);

	/* change AUTH0 value */
	data[15] = startAddress;

	/* Write back data */

	if(HAL_I2C_IsDeviceReady(&hi2c2, nfc_address_recommended, 1, 100)== HAL_OK)
		write_To_NFC(0x38,data,nfc_address_recommended);
	else
		write_To_NFC(0x38,data,nfc_Address);

}


