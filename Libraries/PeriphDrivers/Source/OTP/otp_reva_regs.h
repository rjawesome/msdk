/**
 * @file    otp_reva_regs.h
 * @brief   Registers, Bit Masks and Bit Positions for the OTP_REVA Peripheral Module.
 */

/******************************************************************************
 * Copyright (C) 2022 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 ******************************************************************************/

#ifndef _OTP_REVA_REGS_H_
#define _OTP_REVA_REGS_H_

/* **** Includes **** */
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__ICCARM__)
  #pragma system_include
#endif

#if defined (__CC_ARM)
  #pragma anon_unions
#endif
/// @cond
/*
    If types are not defined elsewhere (CMSIS) define them here
*/
#ifndef __IO
#define __IO volatile
#endif
#ifndef __I
#define __I  volatile const
#endif
#ifndef __O
#define __O  volatile
#endif
#ifndef __R
#define __R  volatile const
#endif
/// @endcond

/* **** Definitions **** */

/**
 * @ingroup     otp_reva
 * @defgroup    otp_reva_registers OTP_REVA_Registers
 * @brief       Registers, Bit Masks and Bit Positions for the OTP_REVA Peripheral Module.
 * @details One-Time Programmable (OTP) Memory Controller.
 */

/**
 * @ingroup otp_reva_registers
 * Structure type to access the OTP_REVA Registers.
 */
typedef struct {
    __IO uint32_t ctrl;                 /**< <tt>\b 0x00:</tt> OTP_REVA CTRL Register */
    __IO uint32_t clkdiv;               /**< <tt>\b 0x04:</tt> OTP_REVA CLKDIV Register */
    __IO uint32_t rdata;                /**< <tt>\b 0x08:</tt> OTP_REVA RDATA Register */
    __IO uint32_t status;               /**< <tt>\b 0x0C:</tt> OTP_REVA STATUS Register */
    __R  uint32_t rsv_0x10_0x2f[8];
    __IO uint32_t wdata;                /**< <tt>\b 0x30:</tt> OTP_REVA WDATA Register */
    __R  uint32_t rsv_0x34_0x3b[2];
    __IO uint32_t actrl0;               /**< <tt>\b 0x3C:</tt> OTP_REVA ACTRL0 Register */
    __IO uint32_t actrl1;               /**< <tt>\b 0x40:</tt> OTP_REVA ACTRL1 Register */
} mxc_otp_reva_regs_t;

/* Register offsets for module OTP_REVA */
/**
 * @ingroup    otp_reva_registers
 * @defgroup   OTP_REVA_Register_Offsets Register Offsets
 * @brief      OTP_REVA Peripheral Register Offsets from the OTP_REVA Base Peripheral Address.
 * @{
 */
 #define MXC_R_OTP_REVA_CTRL                ((uint32_t)0x00000000UL) /**< Offset from OTP_REVA Base Address: <tt> 0x0000</tt> */ 
 #define MXC_R_OTP_REVA_CLKDIV              ((uint32_t)0x00000004UL) /**< Offset from OTP_REVA Base Address: <tt> 0x0004</tt> */ 
 #define MXC_R_OTP_REVA_RDATA               ((uint32_t)0x00000008UL) /**< Offset from OTP_REVA Base Address: <tt> 0x0008</tt> */ 
 #define MXC_R_OTP_REVA_STATUS              ((uint32_t)0x0000000CUL) /**< Offset from OTP_REVA Base Address: <tt> 0x000C</tt> */ 
 #define MXC_R_OTP_REVA_WDATA               ((uint32_t)0x00000030UL) /**< Offset from OTP_REVA Base Address: <tt> 0x0030</tt> */ 
 #define MXC_R_OTP_REVA_ACTRL0              ((uint32_t)0x0000003CUL) /**< Offset from OTP_REVA Base Address: <tt> 0x003C</tt> */ 
 #define MXC_R_OTP_REVA_ACTRL1              ((uint32_t)0x00000040UL) /**< Offset from OTP_REVA Base Address: <tt> 0x0040</tt> */ 
/**@} end of group otp_reva_registers */

/**
 * @ingroup  otp_reva_registers
 * @defgroup OTP_REVA_CTRL OTP_REVA_CTRL
 * @brief    OTP Control Register.
 * @{
 */
 #define MXC_F_OTP_REVA_CTRL_ADDR_POS                   0 /**< CTRL_ADDR Position */
 #define MXC_F_OTP_REVA_CTRL_ADDR                       ((uint32_t)(0x1FFUL << MXC_F_OTP_REVA_CTRL_ADDR_POS)) /**< CTRL_ADDR Mask */

 #define MXC_F_OTP_REVA_CTRL_READ_POS                   10 /**< CTRL_READ Position */
 #define MXC_F_OTP_REVA_CTRL_READ                       ((uint32_t)(0x1UL << MXC_F_OTP_REVA_CTRL_READ_POS)) /**< CTRL_READ Mask */

 #define MXC_F_OTP_REVA_CTRL_WRITE_POS                  11 /**< CTRL_WRITE Position */
 #define MXC_F_OTP_REVA_CTRL_WRITE                      ((uint32_t)(0x1UL << MXC_F_OTP_REVA_CTRL_WRITE_POS)) /**< CTRL_WRITE Mask */

/**@} end of group OTP_REVA_CTRL_Register */

/**
 * @ingroup  otp_reva_registers
 * @defgroup OTP_REVA_CLKDIV OTP_REVA_CLKDIV
 * @brief    OTP Clock Divide Register.
 * @{
 */
 #define MXC_F_OTP_REVA_CLKDIV_CLKDIV_POS               0 /**< CLKDIV_CLKDIV Position */
 #define MXC_F_OTP_REVA_CLKDIV_CLKDIV                   ((uint32_t)(0x3FUL << MXC_F_OTP_REVA_CLKDIV_CLKDIV_POS)) /**< CLKDIV_CLKDIV Mask */

 #define MXC_F_OTP_REVA_CLKDIV_SPWE_POS                 8 /**< CLKDIV_SPWE Position */
 #define MXC_F_OTP_REVA_CLKDIV_SPWE                     ((uint32_t)(0x1UL << MXC_F_OTP_REVA_CLKDIV_SPWE_POS)) /**< CLKDIV_SPWE Mask */

 #define MXC_F_OTP_REVA_CLKDIV_PD_POS                   9 /**< CLKDIV_PD Position */
 #define MXC_F_OTP_REVA_CLKDIV_PD                       ((uint32_t)(0x1UL << MXC_F_OTP_REVA_CLKDIV_PD_POS)) /**< CLKDIV_PD Mask */

 #define MXC_F_OTP_REVA_CLKDIV_RDY_POS                  16 /**< CLKDIV_RDY Position */
 #define MXC_F_OTP_REVA_CLKDIV_RDY                      ((uint32_t)(0x1UL << MXC_F_OTP_REVA_CLKDIV_RDY_POS)) /**< CLKDIV_RDY Mask */

/**@} end of group OTP_REVA_CLKDIV_Register */

/**
 * @ingroup  otp_reva_registers
 * @defgroup OTP_REVA_RDATA OTP_REVA_RDATA
 * @brief    GPIO Clear Function Enable Register. Writing a 1 to one or more bits in this
 *           register clears the bits in the same positions in GPIO_EN to 0, without
 *           affecting other bits in that register.
 * @{
 */
 #define MXC_F_OTP_REVA_RDATA_DATA_POS                  0 /**< RDATA_DATA Position */
 #define MXC_F_OTP_REVA_RDATA_DATA                      ((uint32_t)(0xFFFFFFFFUL << MXC_F_OTP_REVA_RDATA_DATA_POS)) /**< RDATA_DATA Mask */

/**@} end of group OTP_REVA_RDATA_Register */

/**
 * @ingroup  otp_reva_registers
 * @defgroup OTP_REVA_STATUS OTP_REVA_STATUS
 * @brief    OTP Status Register.
 * @{
 */
 #define MXC_F_OTP_REVA_STATUS_BUSY_POS                 0 /**< STATUS_BUSY Position */
 #define MXC_F_OTP_REVA_STATUS_BUSY                     ((uint32_t)(0x1UL << MXC_F_OTP_REVA_STATUS_BUSY_POS)) /**< STATUS_BUSY Mask */

 #define MXC_F_OTP_REVA_STATUS_FAIL_POS                 1 /**< STATUS_FAIL Position */
 #define MXC_F_OTP_REVA_STATUS_FAIL                     ((uint32_t)(0x1UL << MXC_F_OTP_REVA_STATUS_FAIL_POS)) /**< STATUS_FAIL Mask */

 #define MXC_F_OTP_REVA_STATUS_UNLOCK1_POS              8 /**< STATUS_UNLOCK1 Position */
 #define MXC_F_OTP_REVA_STATUS_UNLOCK1                  ((uint32_t)(0x1UL << MXC_F_OTP_REVA_STATUS_UNLOCK1_POS)) /**< STATUS_UNLOCK1 Mask */

 #define MXC_F_OTP_REVA_STATUS_UNLOCK3_POS              9 /**< STATUS_UNLOCK3 Position */
 #define MXC_F_OTP_REVA_STATUS_UNLOCK3                  ((uint32_t)(0x1UL << MXC_F_OTP_REVA_STATUS_UNLOCK3_POS)) /**< STATUS_UNLOCK3 Mask */

/**@} end of group OTP_REVA_STATUS_Register */

/**
 * @ingroup  otp_reva_registers
 * @defgroup OTP_REVA_WDATA OTP_REVA_WDATA
 * @brief    OTP Write Data Register.
 * @{
 */
 #define MXC_F_OTP_REVA_WDATA_DATA_POS                  0 /**< WDATA_DATA Position */
 #define MXC_F_OTP_REVA_WDATA_DATA                      ((uint32_t)(0xFFFFFFFFUL << MXC_F_OTP_REVA_WDATA_DATA_POS)) /**< WDATA_DATA Mask */

/**@} end of group OTP_REVA_WDATA_Register */

/**
 * @ingroup  otp_reva_registers
 * @defgroup OTP_REVA_ACTRL0 OTP_REVA_ACTRL0
 * @brief    Access Control for user block.
 * @{
 */
 #define MXC_F_OTP_REVA_ACTRL0_ADATA_POS                0 /**< ACTRL0_ADATA Position */
 #define MXC_F_OTP_REVA_ACTRL0_ADATA                    ((uint32_t)(0xFFFFFFFFUL << MXC_F_OTP_REVA_ACTRL0_ADATA_POS)) /**< ACTRL0_ADATA Mask */

/**@} end of group OTP_REVA_ACTRL0_Register */

/**
 * @ingroup  otp_reva_registers
 * @defgroup OTP_REVA_ACTRL1 OTP_REVA_ACTRL1
 * @brief    Access Control for sys and user block.
 * @{
 */
 #define MXC_F_OTP_REVA_ACTRL1_ADATA_POS                0 /**< ACTRL1_ADATA Position */
 #define MXC_F_OTP_REVA_ACTRL1_ADATA                    ((uint32_t)(0xFFFFFFFFUL << MXC_F_OTP_REVA_ACTRL1_ADATA_POS)) /**< ACTRL1_ADATA Mask */

/**@} end of group OTP_REVA_ACTRL1_Register */

#ifdef __cplusplus
}
#endif

#endif /* _OTP_REVA_REGS_H_ */