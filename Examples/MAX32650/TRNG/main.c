/**
 * @file
 * @brief      True Random Number Generator (TRNG) example
 * @note       Generates random 32-bit number for first part followed by an
 *             application (AES) with TRNG
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

/* **** Includes **** */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "nvic_table.h"
#include "mxc_errors.h"
#include "trng.h"

/* **** Definitions **** */
#define TRNG_32BIT_RND_NO 4 // Number of 32bit random numbers created
#define LEN 16 // Length of one random number (bytes)

/* **** Globals **** */
unsigned int rnd_no[TRNG_32BIT_RND_NO] = { 0 };
uint8_t var_rnd_no[LEN] = { 0 };
volatile uint8_t TRNG_Async;

// *****************************************************************************
void trng_callback(void *req, int result)
{
    TRNG_Async = 0;
}

void TRNG_Handler(void)
{
    MXC_TRNG_Handler();
}

int main(void)
{
    printf("\n***** TRNG Example *****\n\n");

    MXC_TRNG_Init();

    //Reading and printing rnd 32-bit numbers
    printf("%i Random 32 Bit Integers\n", TRNG_32BIT_RND_NO);
    int i;
    for (i = 0; i < TRNG_32BIT_RND_NO; i++) {
        rnd_no[i] = MXC_TRNG_RandomInt();
        printf("0x%08x\n", rnd_no[i]);
    }

    // Reading and pring rnd number of length LEN
    printf("\nSynchronously Acquired Random %i-Bit Number", LEN * 8);

    MXC_TRNG_Random(var_rnd_no, LEN);

    for (i = 0; i < LEN; i++) {
        if (!(i % 4)) {
            printf("\n%01x-%01x: 0x", i, i + 3);
        }
        printf("%02x", var_rnd_no[i]);
    }

    // Acquire Random number, asynchronously
    printf("\n\nAsynchronusly Acquired Random %i-Bit Number", LEN * 8);
    TRNG_Async = 1;
    MXC_NVIC_SetVector(TRNG_IRQn, TRNG_Handler);
    NVIC_EnableIRQ(TRNG_IRQn);
    MXC_TRNG_RandomAsync(var_rnd_no, LEN, trng_callback);

    while (TRNG_Async) {}

    for (i = 0; i < LEN; i++) {
        if (!(i % 4)) {
            printf("\n%01x-%01x: 0x", i, i + 3);
        }
        printf("%02x", var_rnd_no[i]);
    }

    printf("\n\nExample complete.\n");

    return E_NO_ERROR;
}
