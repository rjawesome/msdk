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

#ifndef LIBRARIES_FCL_INCLUDE_UCL_UCL_AES_CBC_MAC_H_
#define LIBRARIES_FCL_INCLUDE_UCL_UCL_AES_CBC_MAC_H_

#include "ucl/ucl_aes.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */

/** @file ucl_aes_cbc_mac.h
 * @defgroup UCL_CBC_MAC_AES AES CBC_MAC
 * AES in CBC_MAC (Cipher Block Chaining-MAC) mode.
 *
 * @par Header:
 * @link ucl_aes_cbc_mac.h ucl_aes_cbc_mac.h @endlink
 *
 * @ingroup UCL_CBC_MAC
 */

/** <b>AES-CBC_MAC</b>.
 * AES in CBC_MAC (Cipher Block Chaining MAC) mode.
 *
 *
 * @param[out] tmac    Pointer to the outputted MAC
 * @param[in] tmac_byteLen    outputted MAC byte length
 * @param[in]  src    Pointer to the input data
 * @param[in]  len    Data byte length
 * @param[in]  key    Pointer to the AES Key
 * @param[in]  keylen Key byte length:
 *                        @li #UCL_AES_KEYLEN_128
 *                        @li #UCL_AES_KEYLEN_192
 *                        @li #UCL_AES_KEYLEN_256
 *
 * @return Error code
 *
 * @retval #UCL_OK             no error occurred
 * @retval #UCL_INVALID_INPUT  one of the input is the pointer NULL
 * @retval #UCL_INVALID_OUTPUT one of the output is the pointer NULL
 * @retval  #UCL_INVALID_ARG   @p len is not a multiple of
 *                             #UCL_AES_BLOCKSIZE or @p keylen is invalid
 *
 * @ingroup UCL_CBC_MAC_AES
 */
  int ucl_aes_cbc_mac(u8 *tmac, u8 tmac_byteLen, u8 *src, u32 len, u8 *key, u32 keylen);

/** <b>AES-CBC_MAC Init</b>.
 * Initialise AES CBC_MAC Context.
 *
 * @param[out] ctx    Pointer to the context
 * @param[in]  key    Pointer to the AES Key
 * @param[in]  keylen Key byte length:
 *                        @li #UCL_AES_KEYLEN_128
 *                        @li #UCL_AES_KEYLEN_192
 *                        @li #UCL_AES_KEYLEN_256
 *
 * @return Error code
 *
 * @retval #UCL_OK             No error occurred
 * @retval #UCL_INVALID_INPUT  The input is the pointer #NULL
 * @retval #UCL_INVALID_OUTPUT The output is the pointer #NULL
 * @retval #UCL_INVALID_ARG    @p keylen is invalid
 *
 * @ingroup UCL_CBC_MAC_AES
 */
int ucl_aes_cbc_mac_init(ucl_aes_ctx_t *ctx, u8 *key, u32 keylen);

/** <b>AES-CBC_MAC Core</b>.
 * Process the Data.
 *
 * @param[out, in] ctx  Pointer to the context
 * @param[in]     src  Pointer to the data
 * @param[in]     len  Data byte length
 *
 * @pre The byte length must be a multiple of #UCL_AES_BLOCKSIZE.
 *
 * @return Error code
 *
 * @retval #UCL_OK             No error occurred
 * @retval #UCL_INVALID_INPUT  One of the input is the pointer #NULL
 * @retval #UCL_INVALID_OUTPUT The output is the pointer #NULL
 * @retval #UCL_INVALID_ARG    The data byte length is not a multiple of
 *                             #UCL_AES_BLOCKSIZE
 *
 * @ingroup UCL_CBC_MAC_AES
 */
int ucl_aes_cbc_mac_core(ucl_aes_ctx_t *ctx, u8 *src, u32 len);

/**<b>AES-CBC_MAC Finish</b>.
 * Output the MAC and zeroize the context.
 *
 * @param[out] tmac    Pointer to the outputted MAC
 * @param[in] tmac_byteLen    outputted MAC byte length
 * @param[out, in] ctx Pointer to the context
 *
 * @return Error code
 *
 * @retval #UCL_OK             No error occurred
 * @retval #UCL_INVALID_OUTPUT The output is the pointer #NULL
 *
 * @ingroup UCL_CBC_MAC_AES
 */
  int ucl_aes_cbc_mac_finish(u8 *tmac, u32 tmac_byteLen, ucl_aes_ctx_t *ctx);

#ifdef __cplusplus
}
#endif /* __cplusplus  */

#endif // LIBRARIES_FCL_INCLUDE_UCL_UCL_AES_CBC_MAC_H_
