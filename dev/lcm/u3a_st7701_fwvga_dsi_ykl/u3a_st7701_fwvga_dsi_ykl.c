#if defined(BUILD_LK)
#include <platform/mt_gpio.h>
#include <platform/mt_pmic.h>
#else
#include <mt-plat/mt_gpio.h>
#endif

#if !defined(BUILD_LK)
#include <linux/string.h>
#endif
#include "lcm_drv.h"

#if defined(BUILD_LK)
        #define LCM_DEBUG  printf
        #define LCM_FUNC_TRACE() printf("huyl [uboot] %s\n",__func__)
#else
        #define LCM_DEBUG  printk
        #define LCM_FUNC_TRACE() printk("huyl [kernel] %s\n",__func__)
#endif
// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (480)
#define FRAME_HEIGHT (960)

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))

#define REGFLAG_DELAY                                                                   0xFD
#define REGFLAG_END_OF_TABLE                                                            0xFE   // END OF REGISTERS MARKER

// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)                lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)           lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)                                                                          lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)                                      lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)                                                                                   lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)                                   lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)   

struct LCM_setting_table {
    unsigned cmd;
    unsigned char count;
    unsigned char para_list[64];
};

static struct LCM_setting_table lcm_sleep_mode_in_setting[] = {
        // Display off sequence
        {0x28, 0, {0x00}},
        {REGFLAG_DELAY, 20, {}},


        {0x10, 0, {0x00}},
        {REGFLAG_DELAY, 120, {}},
        {REGFLAG_END_OF_TABLE, 0x00, {}}
};
static struct LCM_setting_table lcm_compare_id_setting[] = {
        // Display off sequence
        {0xF0,  5,      {0x55, 0xaa, 0x52,0x08,0x00}},
        {REGFLAG_DELAY, 10, {}},

        {REGFLAG_END_OF_TABLE, 0x00, {}}
};


static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
    unsigned int i;

    for(i = 0; i < count; i++) {
        unsigned cmd = table[i].cmd;

        switch (cmd) {
            case REGFLAG_DELAY :
                MDELAY(table[i].count);
                break;       
            case REGFLAG_END_OF_TABLE :
                break;
            default:
                dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
                MDELAY(2);
        }
    }
        
}

// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{
    memset(params, 0, sizeof(LCM_PARAMS));
    params->type = LCM_TYPE_DSI;
    params->width = FRAME_WIDTH;
    params->dbi.te_mode = LCM_DBI_TE_MODE_DISABLED;
    params->dsi.mode = BURST_VDO_MODE;
    params->dsi.LANE_NUM = LCM_TWO_LANE;
    params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
    params->dsi.data_format.trans_seq = LCM_DSI_TRANS_SEQ_MSB_FIRST;
    params->dsi.data_format.padding = LCM_DSI_PADDING_ON_LSB;
    params->dsi.data_format.format = LCM_DSI_FORMAT_RGB888;
    params->dsi.packet_size = 256;
    params->dsi.intermediat_buffer_num = 2;
    params->dsi.PS = LCM_PACKED_PS_24BIT_RGB888;
    params->dsi.lcm_ext_te_enable = 0;
    params->dsi.vertical_sync_active = 2;
    params->dsi.horizontal_active_pixel = FRAME_WIDTH;
    params->dsi.vertical_backporch = 18;
    params->dsi.lcm_esd_check_table[0].cmd = 10;
    params->dsi.vertical_frontporch = 16;
    params->dsi.lcm_esd_check_table[0].para_list[0] = -100;
    params->dsi.horizontal_sync_active = 4;
    params->dsi.lcm_esd_check_table[1].para_list[0] = 0;
    params->dsi.horizontal_backporch = 28;
    params->height = FRAME_HEIGHT;
    params->dsi.horizontal_frontporch = 20;
    params->dsi.word_count = 1440;
    params->dsi.vertical_active_line = FRAME_HEIGHT;
    params->dsi.cont_clock = 1;
    params->dsi.esd_check_enable = 1;
    params->dsi.customization_esd_check_enable = 1;
    params->dsi.lcm_esd_check_table[0].count = 1;
    params->dsi.lcm_esd_check_table[1].cmd = -27;
    params->dsi.lcm_esd_check_table[1].count = 1;
    params->dsi.PLL_CLOCK = 200;
    params->dsi.ssc_disable = 1;
}

static void lcm_init(void)
{
    unsigned int array[6];

    mt6357_upmu_set_rg_ldo_vldo28_en(1);
    mt6357_upmu_set_rg_ldo_vldo28_1_en(1);
    mt6357_upmu_set_rg_ldo_vldo28_sw_op_en(1);

    MDELAY(100);
    SET_RESET_PIN(1);
    MDELAY(10);
    SET_RESET_PIN(0);
    MDELAY(10);
    SET_RESET_PIN(1);
    MDELAY(120);

    array[0] = 0x110500;
    dsi_set_cmdq(array, 1, 1);
    MDELAY(120);
    array[0] = 0x63902;
    array[1] = 0x177FF;
    array[2] = 0x1000;
    dsi_set_cmdq(array, 3, 1);
    array[1] = 0x77C0;
    array[0] = 0x33902;
    dsi_set_cmdq(array, 2, 1);
    array[0] = 0x33902;
    array[1] = 0x20EC1;
    dsi_set_cmdq(array, 2, 1);
    array[0] = 0x33902;
    array[1] = 0x207C2;
    dsi_set_cmdq(array, 2, 1);
    array[1] = 0x38CC;
    array[0] = 0x23902;
    dsi_set_cmdq(array, 2, 1);
    array[5] = 0xD4;
    array[1] = 0xB0300B0;
    array[0] = 0x113902;
    array[2] = 0xC0C160E;
    array[3] = 0x91F0909;
    array[4] = 0x128F1115;
    dsi_set_cmdq(array, 6, 1);
    array[5] = 0xD4;
    array[1] = 0x90300B1;
    array[0] = 0x113902;
    array[2] = 0x8091610;
    array[3] = 0x822090A;
    array[4] = 0x1B961517;
    dsi_set_cmdq(array, 6, 1);
    array[0] = 0x63902;
    array[1] = 0x177FF;
    array[2] = 0x1100;
    dsi_set_cmdq(array, 3, 1);
    array[1] = 0x4DB0;
    array[0] = 0x23902;
    dsi_set_cmdq(array, 2, 1);
    array[1] = 0x5BB1;
    array[0] = 0x23902;
    dsi_set_cmdq(array, 2, 1);
    array[1] = 0x7B2;
    array[0] = 0x23902;
    dsi_set_cmdq(array, 2, 1);
    array[1] = 0x80B3;
    array[0] = 0x23902;
    dsi_set_cmdq(array, 2, 1);
    array[1] = 0x4EB5;
    array[0] = 0x23902;
    dsi_set_cmdq(array, 2, 1);
    array[1] = 0x87B7;
    array[0] = 0x23902;
    dsi_set_cmdq(array, 2, 1);
    array[1] = 0x20B8;
    array[0] = 0x23902;
    dsi_set_cmdq(array, 2, 1);
    array[1] = 0x3C0;
    array[0] = 0x23902;
    dsi_set_cmdq(array, 2, 1);
    array[1] = 0x78C1;
    array[0] = 0x23902;
    dsi_set_cmdq(array, 2, 1);
    array[1] = 0x78C2;
    array[0] = 0x23902;
    dsi_set_cmdq(array, 2, 1);
    array[1] = 0x88D0;
    array[0] = 0x23902;
    dsi_set_cmdq(array, 2, 1);
    MDELAY(10);
    array[0] = 0x43902;
    array[1] = 0x20000E0;
    dsi_set_cmdq(array, 2, 1);
    array[0] = 0xC3902;
    array[1] = 0x98C07E1;
    array[2] = 0x88C068C;
    array[3] = 0x4444008C;
    dsi_set_cmdq(array, 4, 1);
    array[2] = 0;
    array[0] = 0xE3902;
    array[3] = 0;
    array[1] = 0xE2;
    array[4] = 0;
    dsi_set_cmdq(array, 5, 1);
    array[0] = 342274;
    array[1] = 0x330000E3;
    array[2] = 0x33;
    dsi_set_cmdq(array, 3, 1);
    array[0] = 0x33902;
    array[1] = 0x4444E4;
    dsi_set_cmdq(array, 2, 1);
    array[0] = 0x113902;
    array[1] = 0x8CCA0FE5;
    array[2] = 0x8CCA118C;
    array[3] = 0x8CCA0B8C;
    array[4] = 0x8CCA0D8C;
    array[5] = 0x8C;
    dsi_set_cmdq(array, 6, 1);
    array[0] = 342274;
    array[1] = 0x330000E6;
    array[2] = 0x33;
    dsi_set_cmdq(array, 3, 1);
    array[0] = 0x33902;
    array[1] = 0x4444E7;
    dsi_set_cmdq(array, 2, 1);
    array[0] = 0x113902;
    array[1] = 0x8CCA0EE8;
    array[2] = 0x8CCA108C;
    array[3] = 0x8CCA0A8C;
    array[4] = 0x8CCA0C8C;
    array[5] = 0x8C;
    dsi_set_cmdq(array, 6, 1);
    array[2] = 0;
    array[0] = 0x83902;
    array[1] = 0x2EB;
    dsi_set_cmdq(array, 3, 1);
    array[0] = 0x113902;
    array[1] = 0x7689ABED;
    array[2] = 0xFFFF0154;
    array[3] = 0xFFFFFFFF;
    array[4] = 0x98674510;
    array[5] = 0xBA;
    dsi_set_cmdq(array, 6, 1);
    array[0] = 0x63902;
    array[1] = 0x177FF;
    array[2] = 0x1000;
    dsi_set_cmdq(array, 3, 1);
    array[1] = 0xE5;
    array[0] = 0x23902;
    dsi_set_cmdq(array, 2, 1);
    array[1] = 0x35;
    array[0] = 0x23902;
    dsi_set_cmdq(array, 2, 1);
    array[0] = 0x290500;
    dsi_set_cmdq(array, 1, 1);
    MDELAY(20);
    printk("[LLF_kernel]:u3a_infinish\n");
}

static void lcm_suspend(void)
{
    push_table(lcm_sleep_mode_in_setting, sizeof(lcm_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);
}

static void lcm_resume(void)
{
    lcm_init();

/* ADD FOR PS later
    mt6357_upmu_set_rg_ldo_vldo28_en(1);
    mt6357_upmu_set_rg_ldo_vldo28_1_en(1);
    mt6357_upmu_set_rg_ldo_vldo28_sw_op_en(1);
*/

}
         
static unsigned int lcm_compare_id(void)
{
    return 1;
}

LCM_DRIVER u3a_st7701_fwvga_dsi_ykl_lcm_drv = 
{
    .name           = "u3a_st7701_fwvga_dsi_ykl",
    .set_util_funcs = lcm_set_util_funcs,
    .get_params     = lcm_get_params,
    .init           = lcm_init,
    .suspend        = lcm_suspend,
    .resume         = lcm_resume,
    .compare_id    = lcm_compare_id,
};
