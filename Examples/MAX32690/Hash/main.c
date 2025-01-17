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
 * @brief   Hash Function Example.
 * @details This example demonstrates the Hash Function: SHA-256.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "mxc_device.h"
#include "mxc_sys.h"
#include "ctb.h"

volatile int wait;
volatile int callback_result;
volatile int counter;

/***** Globals *****/

char temp[] = { 0x00, 0x00, 0x00 };

void CRYPTO_IRQHandler(void)
{
    MXC_CTB_Handler();
}

void Test_Callback(void *req, int result)
{
    wait = 0;
    callback_result = result;
}

int Test_Result(int result)
{
    if (result) {
        printf(" * Failed *\n\n");
        return -1;
    } else {
        printf("   Passed  \n\n");
        return 0;
    }
}

void ascii_to_byte(const char *src, char *dst, int len)
{
    int i;

    for (i = 0; i < len; ++i) {
        int val;
        temp[0] = *src;
        src++;
        temp[1] = *src;
        src++;
        sscanf(temp, "%0x", &val);
        dst[i] = val;
    }
}

int Test_Hash(int asynchronous)
{
    printf(asynchronous ? "Test Hash Async\n" : "Test Hash Sync\n");

    unsigned char sha256_msg[] =
        "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890!@#$%&*()";

    char _sha256_result[] = "93bfb2299f7427f021ad038cec5054b4db2e935f3ae10d64e4e6a40a77269803";
    char sha256_result[33];
    ascii_to_byte(_sha256_result, sha256_result, 32);

    unsigned char destination[33];
    unsigned int msgLen = sizeof(sha256_msg) - 1;

    memset(destination, 0, sizeof(destination));

    // Reset Crypto Block
    MXC_CTB_Init(MXC_CTB_FEATURE_HASH);
    MXC_CTB_EnableInt();

    // Select the Hash Function
    MXC_CTB_Hash_SetFunction(MXC_CTB_HASH_SHA256);

    mxc_ctb_hash_req_t hash_req = { sha256_msg, msgLen, destination, &Test_Callback };

    if (asynchronous) {
        wait = 1;
        MXC_CTB_Hash_ComputeAsync(&hash_req);

        while (wait) {}
    } else {
        MXC_CTB_Hash_Compute(&hash_req);
    }

    MXC_CTB_Shutdown(MXC_CTB_FEATURE_HASH);

    if (memcmp(sha256_result, destination, 32)) {
        printf(" * Failed *\n\n");
        return -1;
    }

    printf("   Passed  \n\n");
    return 0;
}

int main(void)
{
    printf("\n\n********** CTB Hash Example **********\n\n");
    int fail = 0;
    fail += Test_Hash(0);
    fail += Test_Hash(1);

    if (fail != 0) {
        printf("\nExample Failed\n");
        return E_FAIL;
    }

    printf("\nExample Succeeded\n");
    return E_NO_ERROR;
}
