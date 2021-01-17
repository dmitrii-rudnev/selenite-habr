/**
  *******************************************************************************
  *
  * @file    dsp_if.c
  * @brief   Digital Signal Processor Interface
  * @version v1.0
  * @date    09.07.2020
  * @author  Dmitrii Rudnev
  *
  *******************************************************************************
  * Copyrigh &copy; 2020 Selenite Project. All rights reserved.
  *
  * This software component is licensed under [BSD 3-Clause license]
  * (http://opensource.org/licenses/BSD-3-Clause/), the "License".<br>
  * You may not use this file except in compliance with the License.
  *******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "dsp_if.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
DSP_Buff_TypeDef dsp_buff;

/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/


/* External variables --------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
 * @brief This function writes a sample to DSP buffer
 *
 * @param a sample to write *
 */

void dsp_buff_write (uint16_t sample)
{
  dsp_buff.buff [dsp_buff.wr_ptr] = sample;
  dsp_buff.wr_ptr++;

  if (dsp_buff.wr_ptr == DSP_BUFF_SIZE) dsp_buff.wr_ptr = 0U;
}

/**
 * @brief This function writes to DSP buffer
 *
 * This function writes to DSP Out buffer and prevent read/write areas overlay
 *
 * @param Source buffer pointer
 * @param Number of bytes to write
 *
 */

void DSP_Out_Buff_Write (uint8_t *pbuf, uint32_t size)
{
  uint32_t i;

  uint16_t *buff = (uint16_t*) pbuf;

  size = size / 2U;

  for (i = 0; i < size; i++)
  {
    dsp_buff_write (buff [i]);
  }
}

/**
 * @brief This function reads from DSP buffer
 *
 *@param Codec TX buffer pointer
 *@param Number of samples to write
 */

void DSP_In_Buff_Read (uint8_t *pbuf, uint32_t size)
{
  if (dsp_buff.buff_enable == 0U)
  {
    dsp_buff.rd_ptr = (dsp_buff.wr_ptr + DSP_BUFF_HALF_SIZE) % DSP_BUFF_SIZE;
    dsp_buff.buff_enable = 1U;
  }

  memcpy (pbuf, (uint8_t*) &dsp_buff.buff[dsp_buff.rd_ptr], size);

  dsp_buff.rd_ptr += size / 2U;

  if (dsp_buff.rd_ptr >= DSP_BUFF_SIZE) dsp_buff.rd_ptr = 0U;
}

/**
 * @brief This function flush DSP Out buffer
 *
 * This function writes to DSP Out buffer zeros
 */

void DSP_Out_Buff_Mute (void)
{
  memset ((uint8_t*) dsp_buff.buff, 0, DSP_BUFF_SIZE * 2U);
}



/****END OF FILE****/
