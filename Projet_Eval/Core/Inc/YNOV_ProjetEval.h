/*
 * YNOV_ProjetEval.h
 *
 *  Created on: Jan 11, 2021
 *      Author: DylanO
 */

#ifndef INC_YNOV_PROJETEVAL_H_
#define INC_YNOV_PROJETEVAL_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>


/* Register Address define */
#define LIS3DSH_CTRL_REG4_ADDR 	0x20
#define LIS3DSH_CTRL_REG5_ADDR 	0x24
#define LIS3DSH_STATUS_ADDR 	0x27
#define LIS3DSH_OUT_X_L_ADDR	0x28
#define LIS3DSH_OUT_X_H_ADDR	0x29
#define LIS3DSH_OUT_Y_L_ADDR	0x2A
#define LIS3DSH_OUT_Y_H_ADDR	0x2B
#define LIS3DSH_OUT_Z_L_ADDR	0x2C
#define LIS3DSH_OUT_Z_H_ADDR	0x2D


/* ---- Configuration parameters define ---- */

/* Define X, Y, Z */
#define LIS3DSH_X_DISABLED		((uint8_t)0x00)
#define LIS3DSH_Y_DISABLED		((uint8_t)0x00)
#define LIS3DSH_Z_DISABLED		((uint8_t)0x00)
#define LIS3DSH_X_ENABLED		((uint8_t)0x01)
#define LIS3DSH_Y_ENABLED		((uint8_t)0x02)
#define LIS3DSH_Z_ENABLED		((uint8_t)0x04)

/* Define the "output data rate"=ODR of "CTRL4_ODR"  */
#define CTRL4_ODR_DOWN			0x00 // Power Down
#define CTRL4_ODR_3				0x10 // 3,125 Hz
#define CTRL4_ODR_6				0x20 // 6,25 Hz
#define CTRL4_ODR_12			0x30 // 12,5 Hz
#define CTRL4_ODR_25			0x40 // 25 Hz
#define CTRL4_ODR_50			0x50 // 50 Hz
#define CTRL4_ODR_100			0x60 // 100 Hz
#define CTRL4_ODR_400			0x70 // 400 Hz
#define CTRL4_ODR_800			0x80 // 800 Hz
#define CTRL4_ODR_1600			0x90 // 1600 Hz

/* Define the Anti-aliasing filter bandwidth = BW of "CTRL5_BW */
#define CTRL5_BW_800	 		0x00 // 800 Hz
#define CTRL5_BW_400			0x80 // 400 Hz
#define CTRL5_BW_200 			0x40 // 200 Hz
#define CTRL5_BW_50 			0xC0 // 50 Hz

/* Define Full-scale selection = FSCALE of "CTRL5_FSCALE */
#define CTRL5_FSCALE_2 			0x00 // 2g
#define CTRL5_FSCALE_4 			0x08 // 4g
#define CTRL5_FSCALE_6			0x10 // 6g
#define CTRL5_FSCALE_8 			0x18 // 8g
#define CTRL5_FSCALE_16 		0x20 // 16g


/* Return status define */
/* #define LIS3DSH_STATUS_OK 			"LIS3DSH OK !\n\r"
#define LIS3DSH_STATUS_ERROR 		"LIS3DSH ERROR !\n\r" */


/* Init Struct */
typedef struct
{
	uint8_t AxeX;
	uint8_t AxeY;
	uint8_t AxeZ;
	uint8_t ctrl4_ODR;
	uint8_t ctrl5_BW;
	uint8_t ctrl5_FSCALE;
}LIS3DSH_init_t;


/* status enum */
typedef enum
{
	LIS3DSH_OK,
	LIS3DSH_ERROR
}LIS3DSH_Status_t;


/* Write Function */
LIS3DSH_Status_t LIS3DSH_Write_reg(SPI_HandleTypeDef *axcelSPI,
									 uint8_t reg_addr,
									 uint8_t *dataW,
									 uint8_t size);

/* Read Function */
LIS3DSH_Status_t LIS3DSH_Read_reg(SPI_HandleTypeDef *axcelSPI,
									uint8_t reg_addr,
									uint8_t *dataR,
									uint8_t size);

/* Init Function */
LIS3DSH_Status_t LIS3DSH_Init(SPI_HandleTypeDef *axcelSPI,
									LIS3DSH_init_t axcelInitDef[]);

/* Get AXIS */
LIS3DSH_Status_t LIS3DSH_Get_Axis_X(SPI_HandleTypeDef *axcelSPI,
									int16_t *axcel);

LIS3DSH_Status_t LIS3DSH_Get_Axis_Y(SPI_HandleTypeDef *axcelSPI,
									int16_t *axcel);

LIS3DSH_Status_t LIS3DSH_Get_Axis_Z(SPI_HandleTypeDef *axcelSPI,
									int16_t *axcel);


#endif /* INC_YNOV_PROJETEVAL_H_ */
