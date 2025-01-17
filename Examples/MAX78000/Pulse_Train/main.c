/******************************************************************************
 *
 * Copyright (C) 2022-2023 Maxim Integrated Products, Inc. All Rights Reserved.
 * (now owned by Analog Devices, Inc.),
 * Copyright (C) 2023 Analog Devices, Inc. All Rights Reserved. This software
 * is proprietary to Analog Devices, Inc. and its licensors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

/**
 * @file main.c
 * @brief Configures and starts four different pulse trains on GPIO LEDs.
 * @details PT0 setup as 2Hz continuous signal that outputs 10110b
 *          PT1 setup as 10Hz continuous square wave
 *
 * @note Interrupts for pulse trains are enabled but the interrupt handler only clears the flags.
 */

/***** Includes *****/
#include <stdio.h>
#include <stdint.h>
#include "board.h"
#include "nvic_table.h"
#include "pt.h"

/***** Definitions *****/
#define ALL_PT 0x03
#define SQ_WV_HZ 10 //Square wave frequency
#define CONT_WV_BPS 2 //Continuous wave bits/sec
#define CONT_WV_PATTERN \
    0x16 //Continuous wave bit pattern (pattern will only output 5 least significant bits)

#if defined(BOARD_EVKIT_V1)
#define CONT_WV_CH 0
#define SQ_WV_CH 1
#elif defined(BOARD_FTHR_REVA)
#define CONT_WV_CH 1
#define SQ_WV_CH 2
#endif

/***** Globals *****/

/***** Functions *****/

// *****************************************************************************
void PT_IRQHandler(void)
{
    printf("flags = 0x%08x\n", MXC_PT_GetFlags());

    MXC_PT_ClearFlags(ALL_PT);
}

// *****************************************************************************
void ContinuousPulseTrain(int ch)
{
    //setup PT configuration
    mxc_pt_cfg_t ptConfig;
    ptConfig.channel = ch;
    ptConfig.bps = CONT_WV_BPS; //bit rate
    ptConfig.ptLength = 5; //bits
    ptConfig.pattern = CONT_WV_PATTERN;
    ptConfig.loop = 0; //continuous loop
    ptConfig.loopDelay = 0;

    MXC_PT_Config(&ptConfig);
    MXC_PT_Start(1 << ch);
}

// *****************************************************************************
void SquareWave(int ch)
{
    uint32_t freq = SQ_WV_HZ; //Hz
    MXC_PT_SqrWaveConfig(ch, freq);
    MXC_PT_Start(1 << ch);
}

// *****************************************************************************
int main(void)
{
    printf("\n\n************************ Pulse Train Demo ************************\n");
#ifdef BOARD_EVKIT_V1
    printf("PT0 (P0.18, pin 12 on camera header J4) = Continuous pattern of 0x%x at %dbps\n",
           CONT_WV_PATTERN, CONT_WV_BPS);
    printf("PT1 (P0.19, pin 4 on display header DSP2) = %dHz square wave\n", SQ_WV_HZ);
#else
    printf("PT1 (P0.19, pin 9 on header J4) = Continuous pattern of 0x%x at %dbps\n",
           CONT_WV_PATTERN, CONT_WV_BPS);
    printf("PT2 (P0.16, pin 11 on header J4) = %dHz square wave\n", SQ_WV_HZ);
#endif

    NVIC_EnableIRQ(PT_IRQn); //enabled default interrupt handler
    MXC_PT_EnableInt(ALL_PT); //enabled interrupts for all PT
    MXC_PT_Init(MXC_PT_CLK_DIV1); //initialize pulse trains

    ContinuousPulseTrain(CONT_WV_CH);
    SquareWave(SQ_WV_CH);

    while (1) {}
}
