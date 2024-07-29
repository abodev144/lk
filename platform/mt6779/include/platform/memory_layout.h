/* Copyright Statement:
*
* This software/firmware and related documentation ("MediaTek Software") are
* protected under relevant copyright laws. The information contained herein
* is confidential and proprietary to MediaTek Inc. and/or its licensors.
* Without the prior written permission of MediaTek inc. and/or its licensors,
* any reproduction, modification, use or disclosure of MediaTek Software,
* and information contained herein, in whole or in part, shall be strictly prohibited.
*/
/* MediaTek Inc. (C) 2017. All rights reserved.
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
#ifndef _H_MEMORY_LAYOUT_H_
#define _H_MEMORY_LAYOUT_H_

#define PL_ATF_BASE			(0x48A00000)
#if CFG_DEVMPU_SUPPORT
#define PL_ATF_MAX_SIZE			(0x200000)
#else
#define PL_ATF_MAX_SIZE			(0x40000)
#endif
#define PL_BOOTARG_BASE			(0x47DD0000)
#define PL_BOOTARG_MAX_SIZE		(0x200000)
#define PL_TEE_BASE			(0x70000000)
#define PL_TEE_MAX_SIZE			(0x3C00000)
#define LK_KERNEL_32_BASE		(0x40008000)
#define LK_KERNEL_32_MAX_SIZE		(0x7C00000)
#define LK_KERNEL_64_BASE		(0x40080000)
#define LK_KERNEL_64_MAX_SIZE		(0x7C00000)
#define LK_DYNAMIC_KERNEL_64_MAX_SIZE	(0xC880000)
#define LK_DT_BASE			(0x57300000)
#define LK_DT_MAX_SIZE			(0x400000)
#define LK_HMAC_BASE			(0x47FD0000)
#define LK_HMAC_MAX_SIZE		(0x1000)
#define LK_SECURE_BOOT_BASE		(0x47FD1000)
#define LK_SECURE_BOOT_MAX_SIZE		(0x1000)
#define LK_RAMDISK_BASE			(0x51C00000)
#define LK_RAMDISK_MAX_SIZE		(0x4000000)
#define LK_LK_BASE			(0x48000000)
#define LK_LK_MAX_SIZE			(0x900000)
#define LK_DL_BASE			(0x48C00000)
#define LK_DL_MAX_SIZE			(0x8000000)
#define LK_LOGO_MAX_SIZE		(0x1000000)
#define LK_ADSP_BASE			(0x55C00000)
#define LK_ADSP_MAX_SIZE		(0x700000)

#endif
