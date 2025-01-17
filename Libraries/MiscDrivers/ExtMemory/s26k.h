/**
 * @file    s26k.h
 * @brief   Cypress s26k driver header file
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

/* Define to prevent redundant inclusion */
#ifndef LIBRARIES_MISCDRIVERS_EXTMEMORY_S26K_H_
#define LIBRARIES_MISCDRIVERS_EXTMEMORY_S26K_H_

/* **** Includes **** */
#include "mxc_device.h"
#include "hpb.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup S26K
 * @{
 */

/* **** Definitions **** */

/* **** Function Prototypes **** */

/**
 * @brief   Configure the S26K.
 * @param   cs      1 for cs 1, 0 for cs 0.
 * @param   base    Base address for the given CS.
 */
void S26K_Init(unsigned cs, uint32_t base);

/**
 * @brief   Get the status register of the S26K.
 * @returns Data in the status register.
 */
uint16_t S26K_GetStatus(void);

/**
 * @brief   Clear the flags in the status register register.
 */
void S26K_ClearStatus(void);

/**
 * @brief   Erase the entire chip.
 * @note    Will take a long time to complete.
 * @returns #E_NO_ERROR if successful, #E_UNKNOWN if not.
 */
int S26K_ChipErase(void);

/**
 * @brief   Check to see if the give sector is blank.
 * @param   addr    Address for the sector we want to check.
 * @returns #E_NO_ERROR if blank, #E_UNINITIALIZED if not.
 */
int S26K_BlankCheck(uint32_t addr);

/**
 * @brief   Check to see if the give sector is blank.
 * @param   addr    Address for the sector we want to erase.
 * @returns #E_NO_ERROR if erase succeeded. #E_UNKNOWN otherwise.
 */
int S26K_SectorErase(uint32_t addr);

/**
 * @brief   Write a 16 bit value to the give address.
 * @param   addr    Address we want to write to.
 * @param   data    Data to write.
 * @returns #E_NO_ERROR if erase succeeded. #E_UNKNOWN otherwise.
 */
int S26K_Write16(uint32_t addr, uint16_t data);

/**
 * @brief   Write data to the s26k buffer and program.
 * @param   addr    Address we want to write to.
 * @param   data    Data to write.
 * @param   len     Number of bytes to write.
 * @returns #E_NO_ERROR if erase succeeded. #E_UNKNOWN otherwise.
 */
int S26K_Write(uint32_t addr, uint16_t *data, unsigned len);

/**
 * @brief   Read the s26k ID.
 * @param   addr    Offset to start reading from.
 * @param   data    Pointer to store the ID.
 * @param   len     Number of ID bytes to read.
 */
void S26K_GetID(uint32_t offset, uint16_t *data, unsigned len);

/**
 * @brief   Read the s26k CFI.
 * @param   addr    Offset to start reading from.
 * @param   data    Pointer to store the CFI.
 * @param   len     Number of CFI bytes to read.
 */
void S26K_GetCFI(uint32_t offset, uint16_t *data, unsigned len);

uint16_t S26K_GetSectorProtection(uint32_t addr);
uint16_t S26K_GetSectorPPB(uint32_t addr);
void S26K_PPBErase(void);
uint16_t S26K_GetPPBLockStatus(void);
void S26K_ClearPBLock(void);
uint16_t S26K_GetDYBStatus(uint32_t addr);
void S26K_SetDYB(uint32_t addr);
void S26K_ClearDYB(uint32_t addr);
void S26K_SetSectorPPB(uint32_t addr);
uint16_t S26K_GetASPStatus(void);
void S26K_WriteBufferAbortReset(void);

/**@} end of group S26K */

#ifdef __cplusplus
}
#endif

#endif // LIBRARIES_MISCDRIVERS_EXTMEMORY_S26K_H_
