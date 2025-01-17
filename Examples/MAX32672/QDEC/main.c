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
 * @file    main.c
 * @brief   QDEC
 * @details This example uses the QDEC.
 */

/***** Includes *****/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "mxc_device.h"
#include "mxc_delay.h"
#include "led.h"
#include "board.h"
#include "qdec.h"

/***** Definitions *****/
#define MAXCNT_FLAG MXC_F_QDEC_INTFL_MAXCNT
#define COMPARE_FLAG MXC_F_QDEC_INTFL_COMPARE

/***** Globals *****/

/***** Functions *****/
void QDEC_IRQHandler(void)
{
    int flags;

    flags = MXC_QDEC_GetFlags();
    MXC_QDEC_ClearFlags(flags);

    if (flags & MAXCNT_FLAG) {
        LED_Toggle(0);
    }

    if (flags & COMPARE_FLAG) {
        LED_Toggle(1);
    }
}

// *****************************************************************************
int main(void)
{
    int error;
    int position, direction;
    int newPosition, newDirection;
    mxc_qdec_req_t req;

    printf("******** QDEC Example ********\n");
    printf("This example shows the Compare function with Reset on\n");
    printf("MAXCNT enabled. An interrupt is set up when a COMPARE\n");
    printf("event and a MAXCNT event occurs.\n");
    printf("\nConfigure the settings to meet the specs of your application.\n");
    printf("Connect your encoder signal pins to QEA (P0_6) and QEB (P0_7).\n");
    printf("\nLED1 (P0_22) will toggle when a MAXCNT event occurs.\n");
    printf("LED2 (P0_23) will toggle when a COMPARE event occurs.\n");
    printf("\nDirection: 0 - Counter-clockwise\n");
    printf("Direction: 1 - Clockwise\n\n");

    // QDEC request
    req.mode = MXC_QDEC_X2_MODE;
    req.swap = MXC_QDEC_SWAP_CW_A_LEADS_B;
    req.sample = MXC_QDEC_FILTER_2_SAMPLES;
    req.clkdiv = MXC_QDEC_CLKDIV_8;
    req.sticky = MXC_QDEC_STICKY_PULSE;
    req.rst = MXC_QDEC_RST_ON_MAXCNT;
    req.func = MXC_QDEC_COMPARE;
    req.initial = 0;
    req.maxcnt = 255;
    req.compare = 128;

    NVIC_EnableIRQ(QDEC_IRQn);

    error = MXC_QDEC_Init(&req);
    if (error != E_NO_ERROR) {
        printf("\nFail to initialize QDEC. Error: %d\n", error);
        while (1) {
            {
            }
        }
    }

    direction = MXC_QDEC_GetDirection();
    position = MXC_QDEC_GetPosition();
    printf("Position: %d  -  Direction: %d\n", position, direction);

    while (1) {
        newDirection = MXC_QDEC_GetDirection();
        newPosition = MXC_QDEC_GetPosition();

        if (position != newPosition || direction != newDirection) {
            if (direction != newDirection) {
                printf("Direction changed!\n");
            }

            direction = newDirection;
            position = newPosition;
            printf("Position: %d  -  Direction: %d\n", position, direction);

            MXC_Delay(MXC_DELAY_MSEC(100));
        }
    }

    return 0;
}
