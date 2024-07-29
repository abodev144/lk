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

#define LOG_TAG "LCM"

#ifndef BUILD_LK
#include <linux/string.h>
#include <linux/kernel.h>
#endif

#include "lcm_drv.h"

#ifdef BUILD_LK
#include <platform/upmu_common.h>
#include <platform/mt_gpio.h>
#include <platform/mt_i2c.h>
#include <platform/mt_pmic.h>
#include <string.h>
#ifndef MACH_FPGA
#include <lcm_pmic.h>
#endif
#elif defined(BUILD_UBOOT)
#include <asm/arch/mt_gpio.h>
#else
#include <mach/mt_pm_ldo.h>
#include <mach/mt_gpio.h>
#endif

#ifdef BUILD_LK
#define LCM_LOGI(string, args...)  dprintf(0, "[LK/"LOG_TAG"]"string, ##args)
#define LCM_LOGD(string, args...)  dprintf(1, "[LK/"LOG_TAG"]"string, ##args)
#else
#define LCM_LOGI(fmt, args...)  pr_notice("[KERNEL/"LOG_TAG"]"fmt, ##args)
#define LCM_LOGD(fmt, args...)  pr_debug("[KERNEL/"LOG_TAG"]"fmt, ##args)
#endif

// ---------------------------------------------------------------------------
//  Extern Functions
// ---------------------------------------------------------------------------
extern int IMM_GetOneChannelValue(int dwChannel, int data[4], int* rawdata); /* ADC function for multiple LCM drivers */
#define AUXADC_LCM_VOLTAGE_CHANNEL     2
static LCM_UTIL_FUNCS lcm_util;

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))
#define MDELAY(n)       (lcm_util.mdelay(n))
#define UDELAY(n)       (lcm_util.udelay(n))


/* --------------------------------------------------------------------------- */
/* Local Functions */
/* --------------------------------------------------------------------------- */

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update) \
    lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update) \
        lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd) lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums) \
        lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd) \
      lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size) \
        lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)

#ifndef BUILD_LK
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/i2c.h>
#include <linux/irq.h>
/* #include <linux/jiffies.h> */
/* #include <linux/delay.h> */
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#endif

/* --------------------------------------------------------------------------- */
/* Local Constants */
/* --------------------------------------------------------------------------- */
#define LCM_DSI_CMD_MODE                                    0
#define FRAME_WIDTH                                     (720)
#define FRAME_HEIGHT                                    (1600)
#define PHYSICAL_WIDTH					(46100)
#define PHYSICAL_HEIGHT					(157230)

#define REGFLAG_DELAY       0xFFFC
#define REGFLAG_UDELAY  0xFFFB
#define REGFLAG_END_OF_TABLE    0xFFFD
#define REGFLAG_RESET_LOW   0xFFFE
#define REGFLAG_RESET_HIGH  0xFFFF

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define GPIO_CTP_RST_PIN      (GPIO2 | 0x80000000)

struct LCM_setting_table {
	unsigned int cmd;
	unsigned char count;
	unsigned char para_list[64];
};

static struct LCM_setting_table lcm_suspend_setting[] = {
	{0x28, 0, {} },
	{REGFLAG_DELAY, 20, {} },	
	{0x10, 0, {} },
	{REGFLAG_DELAY, 120, {} }
};

static struct LCM_setting_table init_setting[] = {
{0x00,1,{0x00}},
{0xFF,3,{0x80,0x09,0x01}},
{0x00,1,{0x80}},
{0xFF,2,{0x80,0x09}},
{0x00,1,{0x93}},
{0xC5,1,{0x6E}},
{0x00,1,{0x97}},
{0xC5,1,{0x6E}},
{0x00,1,{0x9E}},
{0xC5,1,{0x05}},
{0x00,1,{0x9A}},
{0xC5,1,{0xDF}},
{0x00,1,{0x9C}},
{0xC5,1,{0xDF}},
{0x00,1,{0xB6}},
{0xC5,2,{0x3C,0x3C}},
{0x00,1,{0xB8}},
{0xC5,2,{0x55,0x55}},
{0x00,1,{0x00}},
{0xD8,2,{0x35,0x39}},
{0x00,1,{0x01}},
{0xD9,2,{0xE0,0xE0}},
{0x00,1,{0x82}},
{0xC5,1,{0x15}},
{0x00,1,{0x83}},
{0xC5,1,{0x07}},
{0x00,1,{0xB3}},
{0xC5,1,{0xC7}},
{0x00,1,{0xB0}},
{0xC5,1,{0xD7}},
{0x00,1,{0xA9}},
{0xCF,1,{0x56}},
{0x00,1,{0x00}},
{0xE1,16,{0x05,0x09,0x14,0x20,0x28,0x32,0x42,0x4F,0x51,0x5F,0x62,0x7A,0x87,0x71,0x70,0x63}},
{0x00,1,{0x10}},
{0xE1,8,{0x5A,0x4E,0x3D,0x33,0x2A,0x18,0x05,0x00}},
{0x00,1,{0x00}},
{0xE2,16,{0x05,0x09,0x14,0x20,0x28,0x32,0x42,0x4F,0x51,0x5F,0x62,0x7A,0x87,0x71,0x70,0x63}},
{0x00,1,{0x10}},
{0xE2,8,{0x5A,0x4E,0x3D,0x33,0x2A,0x18,0x05,0x00}},
{0x00,1,{0x80}},
{0xCB,7,{0xC1,0xC1,0xFD,0xFD,0xC1,0xC1,0xFD}},
{0x00,1,{0x87}},
{0xCB,1,{0xFD}},
{0x00,1,{0x88}},
{0xCB,8,{0xFD,0xFD,0xC1,0xC1,0xC1,0xC1,0xC1,0xC1}},
{0x00,1,{0x90}},
{0xCB,7,{0xFD,0xC1,0xC1,0xC1,0xC1,0xC2,0xC2}},
{0x00,1,{0x97}},
{0xCB,2,{0xFD,0xCD}},
{0x00,1,{0x99}},
{0xCB,7,{0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
{0x00,1,{0xA0}},
{0xCB,1,{0x00}},
{0x00,1,{0xA1}},
{0xCB,8,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
{0x00,1,{0xA9}},
{0xCB,7,{0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
{0x00,1,{0xB0}},
{0xCB,2,{0x00,0x00}},
{0x00,1,{0xB9}},
{0xCB,7,{0x05,0x05,0x50,0x00,0x50,0x31,0x00}},
{0x00,1,{0xCB}},
{0xC0,1,{0x11}},
{0x00,1,{0x80}},
{0xCC,8,{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x0A}},
{0x00,1,{0x88}},
{0xCC,8,{0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x26}},
{0x00,1,{0x90}},
{0xCC,6,{0x26,0x04,0x02,0x3F,0x08,0x24}},
{0x00,1,{0x80}},
{0xCD,8,{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x12}},
{0x00,1,{0x88}},
{0xCD,8,{0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x26}},
{0x00,1,{0x90}},
{0xCD,6,{0x26,0x03,0x05,0x3F,0x08,0x24}},
{0x00,1,{0xA0}},
{0xCC,8,{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x19}},
{0x00,1,{0xA8}},
{0xCC,8,{0x18,0x17,0x16,0x15,0x14,0x13,0x12,0x24}},
{0x00,1,{0xB0}},
{0xCC,6,{0x26,0x05,0x03,0x3F,0x08,0x26}},
{0x00,1,{0xA0}},
{0xCD,8,{0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x11}},
{0x00,1,{0xA8}},
{0xCD,8,{0x10,0x0F,0x0E,0x0D,0x0C,0x0B,0x0A,0x24}},
{0x00,1,{0xB0}},
{0xCD,6,{0x26,0x02,0x04,0x3F,0x08,0x26}},
{0x00,1,{0xE7}},
{0xCB,1,{0x02}},
{0x00,1,{0xE0}},
{0xC3,4,{0x25,0x00,0x00,0x71}},
{0x00,1,{0x80}},
{0xC2,4,{0x96,0x09,0x16,0xA9}},
{0x00,1,{0x88}},
{0xC2,4,{0x92,0x09,0x16,0xA9}},
{0x00,1,{0x98}},
{0xC2,4,{0x9F,0x09,0x02,0xBD}},
{0x00,1,{0x84}},
{0xC2,4,{0x91,0x09,0x16,0xA9}},
{0x00,1,{0x8C}},
{0xC2,4,{0x95,0x09,0x16,0xA9}},
{0x00,1,{0xB8}},
{0xC2,4,{0x08,0x09,0x00,0xBF}},
{0x00,1,{0xC0}},
{0xC2,7,{0x87,0x08,0x00,0x07,0x20,0x93,0x0F}},
{0x00,1,{0xC7}},
{0xC2,7,{0x85,0x08,0x00,0x07,0x20,0x93,0x0F}},
{0x00,1,{0xD0}},
{0xC2,7,{0x86,0x08,0x00,0x07,0x20,0x93,0x0F}},
{0x00,1,{0xD7}},
{0xC2,7,{0x84,0x08,0x00,0x07,0x20,0x93,0x0F}},
{0x00,1,{0xE0}},
{0xC2,7,{0x8F,0x00,0x00,0x07,0x20,0x93,0x0F}},
{0x00,1,{0xE7}},
{0xC2,7,{0x8D,0x00,0x00,0x07,0x20,0x93,0x0F}},
{0x00,1,{0xF0}},
{0xC2,7,{0x8E,0x00,0x00,0x07,0x20,0x93,0x0F}},
{0x00,1,{0xF7}},
{0xC2,7,{0x8C,0x00,0x00,0x07,0x20,0x93,0x0F}},
{0x00,1,{0x80}},
{0xC3,7,{0x83,0x08,0x00,0x07,0x20,0x93,0x0F}},
{0x00,1,{0x87}},
{0xC3,7,{0x81,0x08,0x00,0x07,0x20,0x93,0x0F}},
{0x00,1,{0x90}},
{0xC3,7,{0x82,0x08,0x00,0x07,0x20,0x93,0x0F}},
{0x00,1,{0x97}},
{0xC3,7,{0x80,0x08,0x00,0x07,0x20,0x93,0x0F}},
{0x00,1,{0xC0}},
{0xCD,7,{0x8B,0x00,0x00,0x07,0x20,0x93,0x0F}},
{0x00,1,{0xC7}},
{0xCD,7,{0x89,0x00,0x00,0x07,0x20,0x93,0x0F}},
{0x00,1,{0xD0}},
{0xCD,7,{0x8A,0x00,0x00,0x07,0x20,0x93,0x0F}},
{0x00,1,{0xD7}},
{0xCD,7,{0x88,0x00,0x00,0x07,0x20,0x93,0x0F}},
{0x00,1,{0xB2}},
{0xCB,7,{0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
{0x00,1,{0xC9}},
{0xF5,1,{0x04}},
{0x00,1,{0x00}},
{0x1C,1,{0x00}},
{0x00,1,{0xA0}},
{0xC1,1,{0xE0}},
{0x00,1,{0xA6}},
{0xC1,1,{0x0E}},
{0x00,1,{0x80}},
{0xCE,1,{0x00}},
{0x00,1,{0xD0}},
{0xCE,1,{0x01}},
{0x00,1,{0xD5}},
{0xCE,1,{0x00}},
{0x00,1,{0xD6}},
{0xCE,1,{0xC8}},
{0x00,1,{0xE0}},
{0xCE,1,{0x00}},
{0x00,1,{0xF0}},
{0xCE,1,{0x00}},
{0x00,1,{0x81}},
{0xC0,1,{0xC0}},
{0x00,1,{0x85}},
{0xC0,1,{0x24}},
{0x00,1,{0x83}},
{0xC0,1,{0xD6}},
{0x00,1,{0xC0}},
{0xCF,4,{0x06,0x06,0x3C,0x40}},
{0x00,1,{0x8C}},
{0xC4,1,{0x10}},
{0x00,1,{0xE6}},
{0xC0,1,{0x40}},
{0x00,1,{0xA3}},
{0xF3,1,{0x80}},
{0x00,1,{0xA3}},
{0xC4,1,{0x01}},
{0x00,1,{0xB4}},
{0xC4,8,{0x6C,0xEC,0x6C,0xEC,0x6C,0xEC,0x6C,0xEC}},
{0x00,1,{0xC8}},
{0xC4,4,{0x02,0x02,0x02,0x02}},
{0x00,1,{0xE7}},
{0xC0,1,{0x03}},
{0x00,1,{0xD0}},
{0xC4,2,{0x00,0x02}},
{0x00,1,{0xD2}},
{0xC4,4,{0x00,0x03,0x00,0x07}},
{0x00,1,{0xD6}},
{0xC4,2,{0x06,0x17}},
{0x00,1,{0xDE}},
{0xC4,2,{0x06,0x1B}},
{0x00,1,{0xD8}},
{0xC4,2,{0x8F,0xF0}},
{0x00,1,{0xDA}},
{0xC4,4,{0x00,0x06,0x06,0x1C}},
{0x00,1,{0xE0}},
{0xC4,8,{0x03,0x13,0x01,0x00,0x00,0x00,0x00,0x00}},
{0x00,1,{0xE8}},
{0xC4,8,{0x03,0x13,0x01,0x00,0x03,0x13,0x01,0x00}},
{0x00,1,{0xF0}},
{0xC4,8,{0x03,0x13,0x01,0x00,0x03,0x13,0x01,0x00}},
{0x00,1,{0xCC}},
{0xC4,3,{0x00,0x01,0x01}},
{0x00,1,{0xF8}},
{0xC4,2,{0x1C,0x1E}},
{0x00,1,{0xFA}},
{0xC4,2,{0xDC,0x1E}},
{0x00,1,{0xFC}},
{0xC4,4,{0x03,0x07,0xAA,0x00}},
{0x00,1,{0xB7}},
{0xF3,1,{0x01}},
{0x00,1,{0x81}},
{0xC6,1,{0x80}},
{0x00,1,{0x82}},
{0xC6,8,{0x00,0x11,0x11,0x00,0x00,0x00,0x00,0x00}},
{0x00,1,{0x8A}},
{0xC6,1,{0x00}},
{0x00,1,{0xA1}},
{0xB3,2,{0x02,0xD0}},
{0x00,1,{0xA3}},
{0xB3,2,{0x06,0x40}},
{0x00,1,{0xB6}},
{0xC3,6,{0xFF,0xF3,0x33,0xFF,0xF3,0x33}},
{0x00,1,{0xC7}},
{0xC3,6,{0xFF,0xF3,0x33,0xFF,0xF3,0x33}},
{0x00,1,{0x80}},
{0xC4,1,{0x15}},
{0x00,1,{0x80}},
{0xA4,1,{0xFC}},
{0x00,1,{0xA0}},
{0xF3,1,{0x01}},
{0x00,1,{0x80}},
{0xC1,2,{0x22,0x22}},
{0x00,1,{0x90}},
{0xC4,1,{0x98}},
{0x00,1,{0x85}},
{0xF5,1,{0x00}},
{0x00,1,{0xB0}},
{0xCA,1,{0x15}},
{0x00,1,{0xB2}},
{0xCA,1,{0x09}},
{0x00,1,{0x81}},
{0xC5,1,{0x03}},
{0x00,1,{0x92}},
{0xCA,1,{0x06}},

	
	{0x11,1,{0x00}},
	{REGFLAG_DELAY,120,{}},
	{0x29,1,{0x00}},
{0x35,1,{0x00}},
	{REGFLAG_DELAY,30,{}},     
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};

static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
	unsigned int i;

	for (i = 0; i < count; i++) {
		unsigned cmd;
		cmd = table[i].cmd;

		switch (cmd) {

			case REGFLAG_DELAY:
				if (table[i].count <= 10)
					MDELAY(table[i].count);
				else
					MDELAY(table[i].count);
				break;

			case REGFLAG_UDELAY:
				UDELAY(table[i].count);
				break;

			case REGFLAG_END_OF_TABLE:
				break;

			default:
				dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
		}
	}
}
/*
static struct LCM_setting_table lcm_initialization_setting[] = {
//VCOM
	{0x41,2,{0x5A,0x03}},
	{0x80,2,{0x75,0x00}},
	
	{0x35,1,{0x00}},
	
	{0x11,1,{0x00}},
	{REGFLAG_DELAY,120,{}},
	{0x29,1,{0x00}},
	{REGFLAG_DELAY,50,{}},     
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};
static void init_lcm_registers(void)
{
   	push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
}*/
/* --------------------------------------------------------------------------- */
/* LCM Driver Implementations */
/* --------------------------------------------------------------------------- */

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
	memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{
	memset(params, 0, sizeof(LCM_PARAMS));

	params->type = LCM_TYPE_DSI;

	params->width = FRAME_WIDTH;
	params->height = FRAME_HEIGHT;
	
	params->physical_width	= PHYSICAL_WIDTH/1000;
	params->physical_height	= PHYSICAL_HEIGHT/1000;

	params->dsi.mode = SYNC_PULSE_VDO_MODE;
	

	/* DSI */
	/* Command mode setting */
	params->dsi.LANE_NUM = LCM_FOUR_LANE;
	/* The following defined the fomat for data coming from LCD engine. */
	params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
	params->dsi.data_format.trans_seq = LCM_DSI_TRANS_SEQ_MSB_FIRST;
	params->dsi.data_format.padding = LCM_DSI_PADDING_ON_LSB;
	params->dsi.data_format.format = LCM_DSI_FORMAT_RGB888;

	/* video mode timing */
		params->dsi.intermediat_buffer_num = 2;  
	params->dsi.PS = LCM_PACKED_PS_24BIT_RGB888;

	params->dsi.vertical_sync_active = 2;
	params->dsi.vertical_backporch = 34;
	params->dsi.vertical_frontporch = 214;
	params->dsi.vertical_active_line = FRAME_HEIGHT;

	params->dsi.horizontal_sync_active = 16;
	params->dsi.horizontal_backporch = 46;
	params->dsi.horizontal_frontporch = 80;
	params->dsi.horizontal_active_pixel = FRAME_WIDTH;
	params->dsi.ssc_disable = 0;// ssc disable control (1: disable, 0: enable, default: 0)
	params->dsi.ssc_range = 1;

	params->dsi.PLL_CLOCK = 286;

//	params->dsi.CLK_HS_POST = 36;
//	params->dsi.clk_lp_per_line_enable = 0;
	params->dsi.esd_check_enable = 1;
	params->dsi.customization_esd_check_enable = 1;
	params->dsi.lcm_esd_check_table[0].cmd = 0x0A;
	params->dsi.lcm_esd_check_table[0].count = 1;
	params->dsi.lcm_esd_check_table[0].para_list[0] = 0x9C;
}

static void lcm_init(void)
{
	int ret = 0;

	SET_RESET_PIN(0);
	mt_set_gpio_mode(GPIO_CTP_RST_PIN, GPIO_MODE_00);
	mt_set_gpio_dir(GPIO_CTP_RST_PIN, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ZERO);	

#ifndef MACH_FPGA
	/*config rt5081 register 0xB2[7:6]=0x3, that is set db_delay=4ms.*/
	ret = PMU_REG_MASK(0xB2, (0x3 << 6), (0x3 << 6));

	/* set AVDD 5.4v, (4v+28*0.05v) 36=5.8v 40=6.0v*/
	/*ret = RT5081_write_byte(0xB3, (1 << 6) | 28);*/
	ret = PMU_REG_MASK(0xB3, 36, (0x3F << 0));
	if (ret < 0)
		LCM_LOGI("ft8006s----AVDD----cmd=%0x--i2c write error----\n", 0xB3);
	else
		LCM_LOGI("ft8006s----AVDD----cmd=%0x--i2c write success----\n", 0xB3);

	/* set AVEE */
	/*ret = RT5081_write_byte(0xB4, (1 << 6) | 28);*/
	ret = PMU_REG_MASK(0xB4, 36, (0x3F << 0));
	if (ret < 0)
		LCM_LOGI("ft8006s----AVEE----cmd=%0x--i2c write error----\n", 0xB4);
	else
		LCM_LOGI("ft8006s----AVEE----cmd=%0x--i2c write success----\n", 0xB4);

	/* enable AVDD & AVEE */
	/* 0x12--default value; bit3--Vneg; bit6--Vpos; */
	/*ret = RT5081_write_byte(0xB1, 0x12 | (1<<3) | (1<<6));*/
	ret = PMU_REG_MASK(0xB1, (1<<3) | (1<<6), (1<<3) | (1<<6));
	if (ret < 0)
		LCM_LOGI("ft8006s----AVDD & AVEE----cmd=%0x--i2c write error----\n", 0xB1);
	else
		LCM_LOGI("ft8006s----AVDD & AVEE----cmd=%0x--i2c write success----\n", 0xB1);

	MDELAY(15);

#endif

	mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ONE);
	SET_RESET_PIN(1);
	MDELAY(10);
	mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ZERO);
	MDELAY(5);
	SET_RESET_PIN(0);
	MDELAY(10);
	mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ONE);
	MDELAY(5);	
	SET_RESET_PIN(1);
	MDELAY(50);

//   init_lcm_registers();
	push_table(init_setting, sizeof(init_setting) / sizeof(struct LCM_setting_table), 1);
}

static void lcm_suspend(void)
{
	int ret;

	push_table(lcm_suspend_setting, sizeof(lcm_suspend_setting) / sizeof(struct LCM_setting_table), 1);
#ifndef MACH_FPGA
	/* enable AVDD & AVEE */
	/* 0x12--default value; bit3--Vneg; bit6--Vpos; */
	/*ret = RT5081_write_byte(0xB1, 0x12);*/
	ret = PMU_REG_MASK(0xB1, (0<<3) | (0<<6), (1<<3) | (1<<6));
	if (ret < 0)
		LCM_LOGI("ft8009b----AVDD & AVEE----cmd=%0x--i2c write error----\n", 0xB1);
	else
		LCM_LOGI("ft8009b----AVDD & AVEE----cmd=%0x--i2c write success----\n", 0xB1);

	MDELAY(5);

#endif
	SET_RESET_PIN(0);
	MDELAY(10);
}

static void lcm_resume(void)
{
	lcm_init();
}

static unsigned int lcm_compare_id(void)
{
	unsigned int id = 0;
	unsigned int version_id;
	unsigned char buffer[2];
	unsigned int array[16];

	SET_RESET_PIN(1);
	SET_RESET_PIN(0);
	MDELAY(1);

	SET_RESET_PIN(1);
	MDELAY(20);

	array[0] = 0x00023700;  /* read id return two byte,version and id */
	dsi_set_cmdq(array, 1, 1);

	read_reg_v2(0xF4, buffer, 2);
	id = buffer[0];     /* we only need ID */

	read_reg_v2(0xDA, buffer, 1); //0xDB
	version_id = buffer[0];

	LCM_LOGI("%s,ft8009_id=0x%08x,version_id=0x%x\n", __func__, id, version_id);
	printf("%s,ft8009_id=0x%08x,version_id=0x%x\n", __func__, id, version_id);
	return (id == 0x40) ? 1 : 0;
	//return 1;
}

LCM_DRIVER ft8009b_hdp1600_dsi_vdo_boe_wanchanglong_lcm_drv = {
	.name = "ft8009b_hdp1600_dsi_vdo_boe_wanchanglong",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params = lcm_get_params,
	.init = lcm_init,
	.suspend = lcm_suspend,
	.resume = lcm_resume,
	.compare_id = lcm_compare_id,
};
