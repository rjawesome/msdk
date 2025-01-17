/**
 * @file        main.c
 * @brief       Instruction cache example
 * @details     Show the time difference when executing operations when instruction
 *              cache is enabled and disabled
 */

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

/***** Includes *****/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mxc_device.h"
#include "icc.h"
#include "rtc.h"
#include "tmr.h"

/***** Functions *****/

/*** Volatile Test Function ***/
void example_func1(void)
{
    volatile int i, j, k;

    // Do 2.5M dummy multiplication operations
    for (i = 0; i < 5000; i++) {
        for (j = 0; j < 500; j++) {
            k = i * j;

            if (((i % 500) == 0) && (j == 1)) {
                printf("%d%%,\t k=%d\n", i / 50, k);
            }
        }
    }

    return;
}

/*** Non-Volatile Test Function ***/
void example_func2(void)
{
    int i, j, k;

    // Do 25M dummy multiplication operations
    for (i = 1; i <= 5000; i++) {
        for (j = 1; j <= 5000; j++) {
            k = i * j;

            if (((i % 500) == 0) && (j == 1)) {
                printf("%d%%,\t k=%d\n", i / 50, k);
            }
        }
    }

    return;
}

// Start timer before test function
void start_timer(void)
{
    MXC_TMR_SW_Start(MXC_TMR0);
    return;
}

// Stop current timer and print elapsed time
int stop_timer(void)
{
    int time_elapsed = MXC_TMR_SW_Stop(MXC_TMR0);
    unsigned int sec = time_elapsed / 1000000;
    unsigned int mili = (time_elapsed - (sec * 1000000)) / 1000;
    unsigned int micro = time_elapsed - (sec * 1000000) - (mili * 1000);
    printf("Time Elapsed: %d.%d%d Seconds\n", sec, mili, micro);
    return time_elapsed;
}

// *****************************************************************************
int main(void)
{
    int fail = 0;
    int icc_en_time = 0;
    int icc_dis_time = 0;

    printf("\n*************** ICC Example ***************\n");

    printf("\n***** 2.5M Operations w/ Volatile Variables Test *****\n");

    printf("\nWith instruction cache enabled:\n");
    MXC_ICC_Enable();
    start_timer();
    example_func1(); // Run test function #1
    icc_en_time = stop_timer();

    printf("\nWith instruction cache disabled:\n");
    MXC_ICC_Disable();
    start_timer();
    example_func1(); // Run test function #1
    icc_dis_time = stop_timer();

    // Check results of 1st test function
    if (icc_dis_time <= icc_en_time) {
        fail += 1;
    }

    MXC_ICC_Flush();
    printf("\n\n***** 25M Operations w/ Non-volatile Variables Test *****\n");

    printf("\nWith instruction cache enabled:\n");
    MXC_ICC_Enable();
    start_timer();
    example_func2(); // Run test function #2
    icc_en_time = stop_timer();

    printf("\nWith instruction cache disabled:\n");
    MXC_ICC_Disable();
    start_timer();
    example_func2(); // Run test function #2
    icc_dis_time = stop_timer();

    // Check results of 2nd Test Function
    if (icc_dis_time <= icc_en_time) {
        fail += 1;
    }

    // Print result
    if (fail != 0) {
        printf("\nExample Failed\n");
        return E_FAIL;
    }

    printf("\nExample Succeeded\n");

    return E_NO_ERROR;
}
