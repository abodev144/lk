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

#ifndef _DDP_REG_MUTEX_H_
#define _DDP_REG_MUTEX_H_

#include "hw/DISP_MUTEX_c_header.h"

#define DISP_OVL_SEPARATE_MUTEX_ID (DISP_MUTEX_DDP_LAST+1)	/* other disp will not see mutex 4 */

#define DISP_REG_CONFIG_MUTEX_INTEN					DISP_MUTEX_INTEN
#define DISP_REG_CONFIG_MUTEX_INTSTA				DISP_MUTEX_INTSTA
#define DISP_REG_CONFIG_MUTEX_CFG					DISP_MUTEX_CFG
	#define CFG_FLD_HW_CG								CFG_FLD_MUTEX_CFG

#define DISP_REG_CONFIG_MUTEX_REG_UPD_TIMEOUT		DISP_REG_UPD_TIMEOUT

#define DISP_REG_CONFIG_MUTEX0_EN					DISP_MUTEX0_EN
	#define EN_FLD_MUTEX0_EN							DISP_MUTEX0_EN_FLD_MUTEX_EN

#define DISP_REG_CONFIG_MUTEX0_RST					DISP_MUTEX0_RST
	#define RST_FLD_MUTEX0_RST							DISP_MUTEX0_RST_FLD_MUTEX_RST

#define DISP_REG_CONFIG_MUTEX0_SOF					DISP_MUTEX0_CTL
	#define SOF_FLD_MUTEX0_SOF							DISP_MUTEX0_CTL_FLD_MUTEX_SOF
	#define SOF_FLD_MUTEX0_SOF_TIMING					DISP_MUTEX0_CTL_FLD_MUTEX_SOF_TIMING
	#define SOF_FLD_MUTEX0_SOF_WAIT						DISP_MUTEX0_CTL_FLD_MUTEX_SOF_WAIT
	#define SOF_FLD_MUTEX0_EOF							DISP_MUTEX0_CTL_FLD_MUTEX_EOF
	#define SOF_FLD_MUTEX0_EOF_TIMING					DISP_MUTEX0_CTL_FLD_MUTEX_EOF_TIMING
	#define SOF_FLD_MUTEX0_EOF_WAIT						DISP_MUTEX0_CTL_FLD_MUTEX_EOF_WAIT

#define SOF_VAL_MUTEX0_SOF_SINGLE_MODE					(0)
#define SOF_VAL_MUTEX0_SOF_FROM_DSI0					(1)
#define SOF_VAL_MUTEX0_SOF_FROM_DSI1					(2)
#define SOF_VAL_MUTEX0_SOF_FROM_DPI						(3)
#define SOF_VAL_MUTEX0_EOF_SINGLE_MODE					(0)
#define SOF_VAL_MUTEX0_EOF_FROM_DSI0					(1)
#define SOF_VAL_MUTEX0_EOF_FROM_DSI1					(2)
#define SOF_VAL_MUTEX0_EOF_FROM_DPI						(3)

#define DISP_REG_CONFIG_MUTEX0_MOD0					DISP_MUTEX0_MOD0

#define DISP_REG_CONFIG_DEBUG_OUT_SEL				DISP_MUTEX_DEBUG_OUT_SEL

#define DISP_REG_CONFIG_MUTEX_EN(n)					(DISP_REG_CONFIG_MUTEX0_EN + (0x20 * (n)))
#define DISP_REG_CONFIG_MUTEX_RST(n)				(DISP_REG_CONFIG_MUTEX0_RST + (0x20 * (n)))
#define DISP_REG_CONFIG_MUTEX_MOD0(n)				(DISP_REG_CONFIG_MUTEX0_MOD0 + (0x20 * (n)))
#define DISP_REG_CONFIG_MUTEX_SOF(n)				(DISP_REG_CONFIG_MUTEX0_SOF + (0x20 * (n)))

#endif