/**
  *******************************************************************************
  *
  * @file    dsp_if.h
  * @brief   Header for dsp_if.c file
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


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_DSP_IF_H_
#define INC_DSP_IF_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "usbd_audio.h"

/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

void DSP_Out_Buff_Write (uint8_t*,  uint32_t);
void DSP_Out_Buff_Mute  (void);
void DSP_In_Buff_Read   (uint8_t*,  uint32_t);

/* Private defines -----------------------------------------------------------*/
#ifndef USBD_AUDIO_FREQ
#define USBD_AUDIO_FREQ          48000U
#endif /* USBD_AUDIO_FREQ */

#ifndef AUDIO_OUT_PACKET_NUM
#define AUDIO_OUT_PACKET_NUM     4U
#endif /* AUDIO_OUT_PACKET_NUM */

#define DSP_BUFF_PACKET_SIZE     (uint16_t)((USBD_AUDIO_FREQ * 2U) / 1000U)                // DSP buffer packet size in samples

#define DSP_BUFF_PACKET_NUM      (uint16_t)(AUDIO_OUT_PACKET_NUM * 4U)
#define DSP_BUFF_SIZE            (uint16_t)((DSP_BUFF_PACKET_SIZE * DSP_BUFF_PACKET_NUM))  // DSP buffer size in samples
#define DSP_BUFF_HALF_SIZE       (uint16_t)((DSP_BUFF_SIZE / 2U))                          // DSP buffer half size

typedef struct
{
  uint16_t buff [DSP_BUFF_SIZE];
  uint8_t  buff_enable;
  uint16_t rd_ptr;
  uint16_t wr_ptr;
} DSP_Buff_TypeDef;


#endif /* INC_DSP_IF_H_ */
