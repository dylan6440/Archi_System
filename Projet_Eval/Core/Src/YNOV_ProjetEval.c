/*
 * YNOV_ProjetEval.c
 *
 *  Created on: Jan 11, 2021
 *      Author: DylanO
 */

#include "YNOV_ProjetEval.h"

float sensitivity = 0.0f;


/* Write Function */
LIS3DSH_Status_t LIS3DSH_Write_reg(SPI_HandleTypeDef *axcelSPI, uint8_t reg_addr, uint8_t *dataW, uint8_t size)
{
	/*   			   0          1           2      */
	/* dataW --> | reg_addr | data_High | data_Low | */
	if(HAL_SPI_Transmit(axcelSPI, dataW, size, 10) == HAL_OK)
	{
		return LIS3DSH_OK;
	}
	return LIS3DSH_ERROR;
}


/* Read Function */
LIS3DSH_Status_t LIS3DSH_Read_reg(SPI_HandleTypeDef *axcelSPI, uint8_t reg_addr, uint8_t *dataR, uint8_t size)
{
	reg_addr |= 0x80;
	if (HAL_SPI_Transmit(axcelSPI, &reg_addr, size, 10) == HAL_OK)
	{
		if(HAL_SPI_Receive(axcelSPI, dataR, size, 10) == HAL_OK)
		{
			return LIS3DSH_OK;
		}
	}
	return LIS3DSH_ERROR;
}


/* Init Function */
LIS3DSH_Status_t LIS3DSH_Init(SPI_HandleTypeDef *axcelSPI, LIS3DSH_init_t *axcelInitDef)
{
	uint8_t spiData = 0x00;
	uint8_t spiCheckData = 0x00;

	/* coef */
switch(axcelInitDef->ctrl5_FSCALE)
{
	case CTRL5_FSCALE_2:
		sensitivity = 0.06f;
		break;
	case CTRL5_FSCALE_4:
		sensitivity = 0.12f;
		break;
	case CTRL5_FSCALE_6:
		sensitivity = 0.18f;
		break;
	case CTRL5_FSCALE_8:
		sensitivity = 0.24f;
		break;
	case CTRL5_FSCALE_16:
		sensitivity = 0.73f;
		break;
}

	// Data register Conf
	spiData |= (axcelInitDef->ctrl4_ODR & 0x80);
	spiData |= (axcelInitDef->ctrl5_BW & 0x00);
	spiData |= (axcelInitDef->ctrl5_FSCALE & 0x00);

	// Data register Conf
	spiData |= (axcelInitDef->AxeX & 0x01);
	spiData |= (axcelInitDef->AxeY & 0x02);
	spiData |= (axcelInitDef->AxeZ & 0x04);
	if(LIS3DSH_Write_reg(axcelSPI, LIS3DSH_STATUS_ADDR, &spiData, 3) == LIS3DSH_OK)
	{
		if(LIS3DSH_Read_reg(axcelSPI, LIS3DSH_STATUS_ADDR, &spiCheckData, 2) == LIS3DSH_OK)
		{
			if(spiCheckData == spiData)
				//&& (spiCheckData[1] == spiData[2])
			{
				return LIS3DSH_OK;
			}
		}
	}
	return LIS3DSH_ERROR;
}


/* Get AXIS Function */
LIS3DSH_Status_t LIS3DSH_Get_Axis_X(SPI_HandleTypeDef *axcelSPI, int16_t *axcel)
{
	int8_t dataR[] = {0x00, 0x00};
	int16_t axcelRaw = 0x0000;

	if(LIS3DSH_Read_reg(axcelSPI, LIS3DSH_OUT_X_L_ADDR, dataR, 2) == LIS3DSH_OK)
	{
	axcelRaw = ((dataR[1] << 8) | dataR[0]) ;
	float axcel =  (axcelRaw * sensitivity);
	return axcel;
	//return LIS3DSH_OK;
	}
	return LIS3DSH_ERROR;
}


/*LIS3DSH_Status_t LIS3DSH_Get_Axis_Y(SPI_HandleTypeDef *axcelSPI, int16_t *axcel)
{
	uint8_t dataR[2] = {0x00,0x00};
	int16_t axcelRaw = 0x0000;

	if(LIS3DSH_Read_reg(axcelSPI, LIS3DSH_OUT_X_L_ADDR, dataR, 2) == LIS3DSH_OK)
	{
		{
		axcelRaw = ((dataR[1] << 8) | dataR[0]) ;
		*axcel = axcelRaw * sensitivity;
		return LIS3DSH_OK;
		}
		return LIS3DSH_ERROR;
}*/


/*LIS3DSH_Status_t LIS3DSH_Get_Axis_Z(SPI_HandleTypeDef *axcelSPI, int16_t *axcel)
{
	uint8_t dataR[2] = {0x00,0x00};
	int16_t axcelRaw = 0x0000;

	if(LIS3DSH_Read_reg(axcelSPI, LIS3DSH_OUT_Z_L_ADDR, dataR, 2) == LIS3DSH_OK)
	{
		{
		axcelRaw = ((dataR[1] << 8) | dataR[0]) ;
		*axcel = axcelRaw * sensitivity;
		return LIS3DSH_OK;
		}
		return LIS3DSH_ERROR;*/
//}



