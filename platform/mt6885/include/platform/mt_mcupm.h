/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2016. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */
#ifndef __MT_MCUPM_H__
#define __MT_MCUPM_H__

//MCUPM use SRAM as GPR
#define MCUPM_SRAM_SIZE			0xC000		//48K Bytes
#define SRAM_32KB_SIZE			0x8000		//32K Bytes
#define SRAM_32KB_AP_BASE		0x1031C000
#define SRAM_RESERVED_20B		0x00000014	//20 Bytes
#define SRAM_GPR_SIZE_4B		0x4		//4 Bytes
#define SRAM_GPR_TOTAL_SIZE		100		//100 Bytes
#define MBOX_TABLE_TOTAL_SIZE		800
#define GPR_BASE_ADDR(x)		(MCUPM_SRAM_SIZE - \
					MBOX_TABLE_TOTAL_SIZE - \
					SRAM_GPR_TOTAL_SIZE + \
					(x * SRAM_GPR_SIZE_4B)) - \
					SRAM_32KB_SIZE + \
					SRAM_32KB_AP_BASE

#define MCUPM_SW_RSTN        0x10300000
#define MCUPM_INFO           GPR_BASE_ADDR(0)
#define MCUPM_BACKUP         GPR_BASE_ADDR(1)
#define MCUPM_TBUF_WPTR      (MCUPM_SW_RSTN + 0x28)
#define MCUPM_PC             (MCUPM_SW_RSTN + 0x40)
#define MCUPM_AHB_STATUS     (MCUPM_SW_RSTN + 0x44)
#define MCUPM_AHB_M0_ADDR    (MCUPM_SW_RSTN + 0x48)
#define MCUPM_AHB_M1_ADDR    (MCUPM_SW_RSTN + 0x4C)
#define MCUPM_LASTK_SZ       GPR_BASE_ADDR(7)
#define MCUPM_LASTK_ADDR     GPR_BASE_ADDR(8)
#define MCUPM_DATA_SZ        GPR_BASE_ADDR(9)
#define MCUPM_DATA_ADDR      GPR_BASE_ADDR(10)
#define MCUPM_RM_ADDR        GPR_BASE_ADDR(12)
#define MCUPM_RM_SZ          GPR_BASE_ADDR(13)
#define MCUPM_DM_ADDR        GPR_BASE_ADDR(14)
#define MCUPM_DM_SZ          GPR_BASE_ADDR(15)
#define MCUPM_TBUF0_L	     (MCUPM_SW_RSTN + 0x0E0)
#define MCUPM_TBUF1_L        (MCUPM_SW_RSTN + 0x0E4)
#define MCUPM_TBUF2_L        (MCUPM_SW_RSTN + 0x0E8)
#define MCUPM_TBUF3_L        (MCUPM_SW_RSTN + 0x0EC)
#define MCUPM_TBUF0_H        (MCUPM_SW_RSTN + 0x0F0)
#define MCUPM_TBUF1_H        (MCUPM_SW_RSTN + 0x0F4)
#define MCUPM_TBUF2_H        (MCUPM_SW_RSTN + 0x0F8)
#define MCUPM_TBUF3_H        (MCUPM_SW_RSTN + 0x0FC)

#define MCUPM_DATA_BUF_SZ       0x400 //same as the size of AEE_LKDUMP_MCUPM_DATA
#define MCUPM_COREDUP_RETRY     10

#define SYSRAM_START_ADDR       0x40100000
#define SYSRAM_END_ADDR         0x40120000
#define DRAM_START_ADDR         0x80000000

#endif /* __MT_MCUPM_H__ */
