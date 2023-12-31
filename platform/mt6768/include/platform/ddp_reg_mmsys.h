/* Copyright Statement:
*
* This software/firmware and related documentation ("MediaTek Software") are
* protected under relevant copyright laws. The information contained herein
* is confidential and proprietary to MediaTek Inc. and/or its licensors.
* Without the prior written permission of MediaTek inc. and/or its licensors,
* any reproduction, modification, use or disclosure of MediaTek Software,
* and information contained herein, in whole or in part, shall be strictly prohibited.
*/
/* MediaTek Inc. (C) 2015. All rights reserved.
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

#ifndef _DDP_REG_MMSYS_H_
#define _DDP_REG_MMSYS_H_

/* field definition */
/* ------------------------------------------------------------- */
/* Config */
#define DISP_REG_CONFIG_MMSYS_INTEN 			(DISPSYS_CONFIG_BASE + 0x0)

#define DISP_REG_CONFIG_MMSYS_CG_CON0			(DISPSYS_CONFIG_BASE + 0x100)
#define DISP_REG_CONFIG_MMSYS_CG_SET0			(DISPSYS_CONFIG_BASE + 0x104)
#define DISP_REG_CONFIG_MMSYS_CG_CLR0			(DISPSYS_CONFIG_BASE + 0x108)
	#define FLD_CG0_26M 							REG_FLD(1, 31)
	#define FLD_CG0_DSI0_IF 						REG_FLD(1, 30)
	#define FLD_CG0_IMG_DL_RELAY				REG_FLD(1, 28)
	#define FLD_CG0_GALS_COMMON1					REG_FLD(1, 22)
	#define FLD_CG0_GALS_COMMON0					REG_FLD(1, 21)
	#define FLD_CG0_SMI_LARB0						REG_FLD(1, 20)
	#define FLD_CG0_SMI_COMMON						REG_FLD(1, 19)
	#define FLD_CG0_DSI0_MM 						REG_FLD(1, 17)
	#define FLD_CG0_DITHER0							REG_FLD(1, 16)
	#define FLD_CG0_GAMMA0							REG_FLD(1, 15)
	#define FLD_CG0_AAL0							REG_FLD(1, 14)
	#define FLD_CG0_CCORR0							REG_FLD(1, 13)
	#define FLD_CG0_COLOR0							REG_FLD(1, 12)
	#define FLD_CG0_WDMA0							REG_FLD(1, 11)
	#define FLD_CG0_RDMA0							REG_FLD(1, 10)
	#define FLD_CG0_DISP_RSZ0 						REG_FLD(1, 9)
	#define FLD_CG0_OVL0_2L							REG_FLD(1, 8)
	#define FLD_CG0_OVL0							REG_FLD(1, 7)

#define DISP_REG_CONFIG_MMSYS_CG_CON1			(DISPSYS_CONFIG_BASE + 0x110)
#define DISP_REG_CONFIG_MMSYS_CG_SET1			(DISPSYS_CONFIG_BASE + 0x114)
#define DISP_REG_CONFIG_MMSYS_CG_CLR1			(DISPSYS_CONFIG_BASE + 0x118)

#define DISP_REG_CONFIG_MMSYS_LCM_RST_B 		(DISPSYS_CONFIG_BASE + 0x150)

#define DISP_REG_CONFIG_SMI_LARB0_GREQ			(DISPSYS_CONFIG_BASE + 0x8DC)

#define DISP_REG_CONFIG_DISP_OVL0_MOUT_EN 		(DISPSYS_CONFIG_BASE + 0xF3C)
#define DISP_REG_CONFIG_DISP_OVL0_2L_MOUT_EN 	(DISPSYS_CONFIG_BASE + 0xF40)
#define DISP_REG_CONFIG_DISP_RSZ0_MOUT_EN 		(DISPSYS_CONFIG_BASE + 0xF44)
#define DISP_REG_CONFIG_DISP_RDMA0_RSZ0_IN_SOUT_SEL (DISPSYS_CONFIG_BASE + 0xF48)
#define DISP_REG_CONFIG_DISP_RDMA0_SOUT_SEL 	(DISPSYS_CONFIG_BASE + 0xF4C)
#define DISP_REG_CONFIG_DITHER0_MOUT_EN 		(DISPSYS_CONFIG_BASE + 0xF50)
#define DISP_REG_CONFIG_DISP_PATH0_SEL_IN 		(DISPSYS_CONFIG_BASE + 0xF54)
#define DISP_REG_CONFIG_DISP_RSZ0_SEL_IN 		(DISPSYS_CONFIG_BASE + 0xF58)
#define DISP_REG_CONFIG_DISP_RDMA0_RSZ0_SEL_IN 	(DISPSYS_CONFIG_BASE + 0xF60)
#define DISP_REG_CONFIG_DISP_COLOR0_OUT_SEL_IN 	(DISPSYS_CONFIG_BASE + 0xF64)
#define DISP_REG_CONFIG_DSI0_SEL_IN 			(DISPSYS_CONFIG_BASE + 0xF68)
#define DISP_REG_CONFIG_DISP_WDMA0_SEL_IN 		(DISPSYS_CONFIG_BASE + 0xF6C)

#define DISP_REG_CONFIG_DISP_MOUT_MASK 			(DISPSYS_CONFIG_BASE + 0x8A0)
#define DISP_REG_CONFIG_DISP_MOUT_MASK1 		(DISPSYS_CONFIG_BASE + 0x8A4)

#define DISP_REG_CONFIG_DISP_DL_VALID_0 		(DISPSYS_CONFIG_BASE + 0xFB0)
#define DISP_REG_CONFIG_DISP_DL_VALID_1 		(DISPSYS_CONFIG_BASE + 0xFB4)
#define DISP_REG_CONFIG_DISP_DL_VALID_2 		(DISPSYS_CONFIG_BASE + 0xFB8)

#define DISP_REG_CONFIG_DISP_DL_READY_0 		(DISPSYS_CONFIG_BASE + 0xFC0)
#define DISP_REG_CONFIG_DISP_DL_READY_1 		(DISPSYS_CONFIG_BASE + 0xFC4)
#define DISP_REG_CONFIG_DISP_DL_READY_2 		(DISPSYS_CONFIG_BASE + 0xFC8)


/* SMI_LARB0 */
#define DISP_REG_SMI_LARB0_MMU_EN			 	(DISPSYS_SMI_LARB0_BASE+0x380)
#define REG_FLD_MMU_EN								REG_FLD(1, 0)

/* field definition */
/* ------------------------------------------------------------- */

#endif
