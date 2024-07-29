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

static LCM_UTIL_FUNCS lcm_util;

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))
#define MDELAY(n)       (lcm_util.mdelay(n))
#define UDELAY(n)       (lcm_util.udelay(n))

#define GPIO_LCM_PWR_EN      GPIO107
#define GPIO_LCM_RST      GPIO45
#define GPIO_LCM_LDO_1V8      GPIO175



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
#define FRAME_WIDTH                                     (800)
#define FRAME_HEIGHT                                    (1280)

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

struct LCM_setting_table {
	unsigned int cmd;
	unsigned char count;
	unsigned char para_list[64];
};

static struct LCM_setting_table lcm_suspend_setting[] = {
    {0x28, 1, {0x00}},
    {REGFLAG_DELAY, 10, {}},
    {0x10, 1, {0x00}},
    {REGFLAG_DELAY, 120, {} },
};

#if 1
static struct LCM_setting_table init_setting[] = {
{0xFF,03,{0x98,0x81,0x03}},
//GIP_1
{0x01,01,{0x00}},
{0x02,01,{0x00}},
{0x03,01,{0x73}},        //STVA
{0x04,01,{0xD7}},        //STVB
{0x05,01,{0x00}},        //STVC
{0x06,01,{0x08}},        //STVA_Rise
{0x07,01,{0x11}},        //STVB_Rise
{0x08,01,{0x00}},        //STVC_Rise
{0x09,01,{0x3F}},    // STV遵僅躲CLK覃淕珨欴遵  //FTI1R(A)
{0x0a,01,{0x00}},        //FTI2R(B)
{0x0b,01,{0x00}},        //FTI3R(C)
{0x0c,01,{0x00}},        //FTI1F(A)
{0x0d,01,{0x00}},        //FTI2F(B)
{0x0e,01,{0x00}},        //FTI2F(C)
{0x0f,01,{0x3F}},   //26  Duty=42%  //CLW1(ALR) Duty=45%
{0x10,01,{0x3F}},   // 26         //CLW2(ARR) Duty=45%
{0x11,01,{0x00}},           
{0x12,01,{0x00}},        
{0x13,01,{0x00}},        //CLWX(ATF)
{0x14,01,{0x00}},
{0x15,01,{0x00}},        //GPMRi(ALR)
{0x16,01,{0x00}},        //GPMRii(ARR)
{0x17,01,{0x00}},        //GPMFi(ALF)
{0x18,01,{0x00}},        //GPMFii(AFF)
{0x19,01,{0x00}},
{0x1a,01,{0x00}},
{0x1b,01,{0x00}},   
{0x1c,01,{0x00}},
{0x1d,01,{0x00}},
{0x1e,01,{0x40}},        //CLKA 40自動反 C0手動反(X8參考CLKB)
{0x1f,01,{0x80}},        //C0
{0x20,01,{0x06}},        //CLKA_Rise
{0x21,01,{0x01}},        //CLKA_Fall
{0x22,01,{0x00}},        //CLKB_Rise(keep toggle需設CLK A後一格)
{0x23,01,{0x00}},        //CLKB_Fall
{0x24,01,{0x00}},        //CLK keep toggle(AL) 8X往左看
{0x25,01,{0x00}},        //CLK keep toggle(AR) 8X往左看
{0x26,01,{0x00}},
{0x27,01,{0x00}},
{0x28,01,{0x33}},       //CLK Phase
{0x29,01,{0x33}},       //CLK overlap
{0x2a,01,{0x00}},  
{0x2b,01,{0x00}},
{0x2c,01,{0x00}},       //GCH R
{0x2d,01,{0x00}},       //GCL R 
{0x2e,01,{0x00}},       //GCH F        
{0x2f,01,{0x00}},       //GCL F
{0x30,01,{0x00}},
{0x31,01,{0x00}},
{0x32,01,{0x00}},       //GCH/L ext2/1行為  5E 01:31   5E 00:42
{0x33,01,{0x00}},
{0x34,01,{0x00}},       //VDD1&2 non-overlap 04:2.62us
{0x35,01,{0x00}},       //GCH/L 區間 00:VS前 01:VS後 10:跨VS 11:frame中       
{0x36,01,{0x00}},
{0x37,01,{0x00}},       //GCH/L
{0x38,01,{0x00}},	//VDD1&2 toggle 1sec
{0x39,01,{0x00}},
{0x3a,01,{0x00}}, 
{0x3b,01,{0x00}},
{0x3c,01,{0x00}},
{0x3d,01,{0x00}},
{0x3e,01,{0x00}},
{0x3f,01,{0x00}},
{0x40,01,{0x00}},
{0x41,01,{0x00}},
{0x42,01,{0x00}},
{0x43,01,{0x00}},       //GCH/L
{0x44,01,{0x00}},
//GIP_2
{0x50,01,{0x01}},
{0x51,01,{0x23}},
{0x52,01,{0x44}},
{0x53,01,{0x67}},
{0x54,01,{0x89}},
{0x55,01,{0xab}},
{0x56,01,{0x01}},
{0x57,01,{0x23}},
{0x58,01,{0x45}},
{0x59,01,{0x67}},
{0x5a,01,{0x89}},
{0x5b,01,{0xab}},
{0x5c,01,{0xcd}},
{0x5d,01,{0xef}},
//GIP_3
{0x5e,01,{0x00}},
{0x5f,01,{0x0C}},     //FW_CGOUT_L[1]    CLK6
{0x60,01,{0x0C}},     //FW_CGOUT_L[2]    CLK6
{0x61,01,{0x0F}},     //FW_CGOUT_L[3]    CLK4
{0x62,01,{0x0F}},     //FW_CGOUT_L[4]    CLK4
{0x63,01,{0x0E}},     //FW_CGOUT_L[5]    CLK2
{0x64,01,{0x0E}},     //FW_CGOUT_L[6]    CLK2
{0x65,01,{0x06}},     //FW_CGOUT_L[7]    STV2
{0x66,01,{0x07}},     //FW_CGOUT_L[8]    STV4
{0x67,01,{0x0D}},     //FW_CGOUT_L[9]    CLK8
{0x68,01,{0x02}},     //FW_CGOUT_L[10]   
{0x69,01,{0x02}},     //FW_CGOUT_L[11]     
{0x6a,01,{0x02}},     //FW_CGOUT_L[12]  
{0x6b,01,{0x02}},     //FW_CGOUT_L[13]   
{0x6c,01,{0x02}},     //FW_CGOUT_L[14]      
{0x6d,01,{0x02}},     //FW_CGOUT_L[15]   
{0x6e,01,{0x0D}},     //FW_CGOUT_L[16]   CLK8    
{0x6f,01,{0x02}},     //FW_CGOUT_L[17]   VGL
{0x70,01,{0x02}},     //FW_CGOUT_L[18]   VGL
{0x71,01,{0x05}},     //FW_CGOUT_L[19]   VDD
{0x72,01,{0x01}},     //FW_CGOUT_L[20]   VDS
{0x73,01,{0x08}},     //FW_CGOUT_L[21]   STV0
{0x74,01,{0x00}},     //FW_CGOUT_L[22]   VSD
{0x75,01,{0x0C}},     //BW_CGOUT_L[1]   
{0x76,01,{0x0C}},     //BW_CGOUT_L[2]    
{0x77,01,{0x0F}},     //BW_CGOUT_L[3]    
{0x78,01,{0x0F}},     //BW_CGOUT_L[4]    
{0x79,01,{0x0E}},     //BW_CGOUT_L[5]     
{0x7a,01,{0x0E}},     //BW_CGOUT_L[6]     
{0x7b,01,{0x06}},     //BW_CGOUT_L[7]   
{0x7c,01,{0x07}},     //BW_CGOUT_L[8]    
{0x7d,01,{0x0D}},     //BW_CGOUT_L[9]      
{0x7e,01,{0x02}},     //BW_CGOUT_L[10]
{0x7f,01,{0x02}},     //BW_CGOUT_L[11]    
{0x80,01,{0x02}},     //BW_CGOUT_L[12]   
{0x81,01,{0x02}},     //BW_CGOUT_L[13] 
{0x82,01,{0x02}},     //BW_CGOUT_L[14]      
{0x83,01,{0x02}},     //BW_CGOUT_L[15]   
{0x84,01,{0x0D}},     //BW_CGOUT_L[16]      
{0x85,01,{0x02}},     //BW_CGOUT_L[17]
{0x86,01,{0x02}},     //BW_CGOUT_L[18]
{0x87,01,{0x05}},     //BW_CGOUT_L[19]
{0x88,01,{0x01}},     //BW_CGOUT_L[20]   
{0x89,01,{0x08}},     //BW_CGOUT_L[21]   
{0x8A,01,{0x00}},     //BW_CGOUT_L[22]   
//CMD_Page 4
{0xFF,03,{0x98,0x81,0x04}},
{0x6E,01,{0x3B}},           //VGH 18V
{0x6F,01,{0x57}},           // reg vcl + pumping ratio VGH=4x VGL=-3x
{0x3A,01,{0x24}},        //A4     //POWER SAVING
{0x8D,01,{0x1F}},           //VGL -12V
{0x87,01,{0xBA}},           //ESD
{0xB2,01,{0xD1}},
{0x88,01,{0x0B}},
{0x38,01,{0x01}},      
{0x39,01,{0x00}},
{0xB5,01,{0x07}},           //gamma bias
{0x31,01,{0x75}},
{0x3B,01,{0x98}},
//CMD_Page 1
{0xFF,03,{0x98,0x81,0x01}},
{0x22,01,{0x0A}},          //BGR, SS
{0x31,01,{0x09}},          //Zig-zag
{0x35,01,{0x07}},          //
{0x53,01,{0x7B}},          //VCOM1
{0x55,01,{0x40}},          //VCOM2 
{0x50,01,{0x86}},   // 4.3 95          //VREG1OUT 4.5V
{0x51,01,{0x82}},    //4.3 90          //VREG2OUT -4.5V
{0x60,01,{0x27}},   //  SDT=2.8 
{0x62,01,{0x20}},
//============Gamma START=============
{0xA0,01,{0x00}},
{0xA1,01,{0x12}},
{0xA2,01,{0x20}},
{0xA3,01,{0x13}},
{0xA4,01,{0x14}},
{0xA5,01,{0x27}},
{0xA6,01,{0x1D}},
{0xA7,01,{0x1F}},
{0xA8,01,{0x7C}},
{0xA9,01,{0x1D}},
{0xAA,01,{0x2A}},
{0xAB,01,{0x6B}},
{0xAC,01,{0x1A}},
{0xAD,01,{0x18}},
{0xAE,01,{0x4E}},
{0xAF,01,{0x24}},
{0xB0,01,{0x2A}},
{0xB1,01,{0x4D}},
{0xB2,01,{0x5B}},
{0xB3,01,{0x23}},
//Neg Register
{0xC0,01,{0x00}},
{0xC1,01,{0x13}},
{0xC2,01,{0x20}},
{0xC3,01,{0x12}},
{0xC4,01,{0x15}},
{0xC5,01,{0x28}},
{0xC6,01,{0x1C}},
{0xC7,01,{0x1E}},
{0xC8,01,{0x7B}},
{0xC9,01,{0x1E}},
{0xCA,01,{0x29}},
{0xCB,01,{0x6C}},
{0xCC,01,{0x1A}},
{0xCD,01,{0x19}},
{0xCE,01,{0x4D}},
{0xCF,01,{0x22}},
{0xD0,01,{0x2A}},
{0xD1,01,{0x4D}},
{0xD2,01,{0x5B}},
{0xD3,01,{0x23}},
//============ Gamma END===========
//CMD_Page 0			
{0xFF,03,{0x98,0x81,0x00}},

	{0x11,1,{0x00}},
	{REGFLAG_DELAY, 120,{}},
	{0x29,1,{0x00}},	
	{REGFLAG_DELAY, 20,{}},
	{0x35,1,{0x00}},
	{REGFLAG_END_OF_TABLE, 0x00, {} }
};
#else

#endif

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
	
		params->type   = LCM_TYPE_DSI;

		params->width  = FRAME_WIDTH;
		params->height = FRAME_HEIGHT;

//		params->physical_width = 108;
//		params->physical_height = 172;
		// enable tearing-free
//		params->dbi.te_mode = LCM_DBI_TE_MODE_DISABLED;
//		params->dbi.te_edge_polarity = LCM_POLARITY_RISING;		
		
        #if (LCM_DSI_CMD_MODE)
		params->dsi.mode   = CMD_MODE;
        #else
		params->dsi.mode   = SYNC_PULSE_VDO_MODE; //SYNC_PULSE_VDO_MODE;//BURST_VDO_MODE; 
        #endif
	
		// DSI
		/* Command mode setting */
		//1 Three lane or Four lane
		params->dsi.LANE_NUM				= LCM_FOUR_LANE;
		//The following defined the fomat for data coming from LCD engine.
		params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
		params->dsi.data_format.trans_seq   = LCM_DSI_TRANS_SEQ_MSB_FIRST;
		params->dsi.data_format.padding     = LCM_DSI_PADDING_ON_LSB;
		params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;


		params->dsi.packet_size=256;

		// Video mode setting		
		params->dsi.intermediat_buffer_num = 0;

		params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;
//		params->dsi.word_count=720*3;	
		
		
		params->dsi.vertical_sync_active				= 4;
		params->dsi.vertical_backporch					= 8;
		params->dsi.vertical_frontporch					= 16;		
		params->dsi.vertical_active_line				= FRAME_HEIGHT; 
		params->dsi.horizontal_sync_active				= 18;
		params->dsi.horizontal_backporch				= 18;
		params->dsi.horizontal_frontporch				= 18;

		params->dsi.horizontal_active_pixel				= FRAME_WIDTH;
		//params->dsi.compatibility_for_nvk = 0;
        params->dsi.PLL_CLOCK = 250; // 260 
		params->dsi.clk_lp_per_line_enable = 1;
		params->dsi.ssc_disable = 1;
		params->dsi.cont_clock= 0;
		
				
		params->dsi.esd_check_enable = 0;
		params->dsi.customization_esd_check_enable = 1;
		params->dsi.lcm_esd_check_table[0].cmd          = 0x0a;
		params->dsi.lcm_esd_check_table[0].count        = 1;
		params->dsi.lcm_esd_check_table[0].para_list[0] = 0x9C;

}


static void lcm_init(void)
{
	
    mt_set_gpio_mode(GPIO_LCM_PWR_EN, GPIO_MODE_00);
    mt_set_gpio_dir(GPIO_LCM_PWR_EN, GPIO_DIR_OUT);
    mt_set_gpio_out(GPIO_LCM_PWR_EN, GPIO_OUT_ONE);
	MDELAY(10);	
	
	mt_set_gpio_mode(GPIO_LCM_LDO_1V8, GPIO_MODE_00);
    mt_set_gpio_dir(GPIO_LCM_LDO_1V8, GPIO_DIR_OUT);
    mt_set_gpio_out(GPIO_LCM_LDO_1V8, GPIO_OUT_ONE);
	
	mt_set_gpio_mode(GPIO_LCM_RST, GPIO_MODE_00);
    mt_set_gpio_dir(GPIO_LCM_RST, GPIO_DIR_OUT);
    mt_set_gpio_out(GPIO_LCM_RST, GPIO_OUT_ZERO);
	MDELAY(10);	

    mt_set_gpio_out(GPIO_LCM_RST, GPIO_OUT_ONE);
	MDELAY(10);
    mt_set_gpio_out(GPIO_LCM_RST, GPIO_OUT_ZERO);
	MDELAY(2);
    mt_set_gpio_out(GPIO_LCM_RST, GPIO_OUT_ONE);
	MDELAY(10);

//	SET_RESET_PIN(0);
//	SET_RESET_PIN(1);
//	MDELAY(10);///1
//	SET_RESET_PIN(0);
//	MDELAY(10);//10
//	SET_RESET_PIN(1);
//	MDELAY(10);//10
#if 1
	push_table(init_setting, sizeof(init_setting) / sizeof(struct LCM_setting_table), 1);
#else	

#endif
}

static void lcm_suspend(void)
{
	push_table(lcm_suspend_setting, sizeof(lcm_suspend_setting) / sizeof(struct LCM_setting_table), 1);
	SET_RESET_PIN(0);
	MDELAY(10);
}

static void lcm_resume(void)
{
	lcm_init();
}

extern void DSI_clk_HS_mode(char enter);
static unsigned int lcm_compare_id(void)
{
	unsigned int id=0;
	unsigned char buffer[3];
	unsigned int array[16]; 
	unsigned int  id_high=0;
	unsigned int  id_low=0;
	
	struct LCM_setting_table switch_table_page1[] = {
		{ 0xFF, 0x03, {0x98, 0x81, 0x01} }
	};
	struct LCM_setting_table switch_table_page0[] = {
		{ 0xFF, 0x03, {0x98, 0x81, 0x00} }
	};	
    mt_set_gpio_mode(GPIO_LCM_PWR_EN, GPIO_MODE_00);
    mt_set_gpio_dir(GPIO_LCM_PWR_EN, GPIO_DIR_OUT);
    mt_set_gpio_out(GPIO_LCM_PWR_EN, GPIO_OUT_ONE);
	MDELAY(10);	
	
	mt_set_gpio_mode(GPIO_LCM_LDO_1V8, GPIO_MODE_00);
    mt_set_gpio_dir(GPIO_LCM_LDO_1V8, GPIO_DIR_OUT);
    mt_set_gpio_out(GPIO_LCM_LDO_1V8, GPIO_OUT_ONE);
	
	SET_RESET_PIN(1);
	SET_RESET_PIN(0);
	MDELAY(1);

	SET_RESET_PIN(1);
	MDELAY(20);
	
	push_table(switch_table_page1, sizeof(switch_table_page1) / sizeof(struct LCM_setting_table), 1);
	
	array[0] = 0x00023700;	/* read id return two byte,version and id */
	dsi_set_cmdq(array, 1, 1);	
	
	read_reg_v2(0x00, buffer, 1);
	id_high = buffer[0]; 	/* we only need ID */

	read_reg_v2(0x01, buffer, 1);
	id_low = buffer[0];
	
	read_reg_v2(0x02, buffer, 1);
	id = buffer[0];

	printf("%s,ili9881c_id_high=0x%x,id_low=0x%x,id=0x%x\n", __func__, id_high, id_low,id);	
	
	push_table(switch_table_page0, sizeof(switch_table_page0) / sizeof(struct LCM_setting_table), 1);		

	if (id_high == 0x98 && id_low == 0x81)
		return 1;
	else
		return 0;
}
LCM_DRIVER ili9881c_wxga_dsi_vdo_hongzhan_lcm_drv = 
{
    .name			= "ili9881c_wxga_dsi_vdo_hongzhan",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
	.compare_id    = lcm_compare_id,

};

