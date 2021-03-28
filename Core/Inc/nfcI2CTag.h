/*
 * nfcI2CTag.h
 *
 *  Created on: 28 mars 2021
 *      Author: Sidi NAMOU
 *      mail: sidi.namou1996@gmail.com
 */

#ifndef INC_NFCI2CTAG_H_
#define INC_NFCI2CTAG_H_

#include "stm32l4xx_hal.h"

#define nfc_Address				0x55 << 1	/* Slave address  by default*/

#define nfc_address_recommended		0x04	/* Slave address recommended by NXP */


#define PWD_AUTH				0x12345678			/*You put your desired Password here */


extern I2C_HandleTypeDef hi2c2;
extern UART_HandleTypeDef huart2;

/**This Function is used to write to a memory address
 * This function is written basing on datasheet of NFC tag I2C plus
 *
 * data is pointer to data, it's size must be 16 bytes
 * MemAddr is the memory address to write to
 *
 * */

void write_To_NFC(uint8_t MemAddr, uint8_t * data, uint8_t nfc_add);



/**This Function is used to read data from NFC at memory address
 * This function is written basing on data sheet of NFC tag I2C plus
 *
 * buffer is pointer to where to store data, it's size must be 16 bytes
 * MemAddr is the memory address to read from
 *
 *
 * */

void read_From_NFC(uint8_t MemAddr, uint8_t * buffer, uint8_t nfc_add);



/*This function is used to change slave address to slave address recommended
 * It has no arguments
 * */

void change_Slave_Address_To_Recommended_address();


/*This function is used to change password
 * If you want to set your own password please change PWD_AUTH Macro definition
 *
 * */

void change_PWD();



/**This function is used to configure a protected memory
 *
 * The user memory is between 0x04 and 0xE1
 *
 * So it may you will want to less some area for unprotected
 *
 * start address is between 0x04 and 0xE1
 * For more details refer to datasheet.
 * */

void autentification_Area(uint8_t startAddress);


#endif /* INC_NFCI2CTAG_H_ */
