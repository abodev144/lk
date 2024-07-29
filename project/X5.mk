LOCAL_DIR := $(GET_LOCAL_DIR)
TARGET := X5
MODULES += app/mt_boot \
           dev/lcm
MTK_EMMC_SUPPORT = yes
DEFINES += MTK_NEW_COMBO_EMMC_SUPPORT
MTK_KERNEL_POWER_OFF_CHARGING = yes
MTK_LCM_PHYSICAL_ROTATION = 0
CUSTOM_LK_LCM = "hct_hx8394f_dsi_vdo_hd_cmi hct_rm68200_dsi_vdo_hd_cpt hct_ili9881_dsi_vdo_hd_cpt hct_otm1282_dsi_vdo_hd_auo hct_otm1285a_dsi_vdo_hd_boe hct_nt35521s_dsi_vdo_hd_boe_50_xld hct_hx8394d_dsi_vdo_hd_cmi"
MTK_SECURITY_SW_SUPPORT = yes
MTK_SEC_FASTBOOT_UNLOCK_SUPPORT = yes
MTK_VERIFIED_BOOT_SUPPORT = yes
BOOT_LOGO := hd720
#DEFINES += WITH_DEBUG_DCC=1
#DEFINES += WITH_DEBUG_UART=1
#DEFINES += WITH_DEBUG_FBCON=1
#DEFINES += MACH_FPGA=y
#DEFINES += MACH_FPGA_NO_DISPLAY
TRUSTONIC_TEE_SUPPORT=no
MTK_GOOGLE_TRUSTY_SUPPORT=no
MTK_DM_VERITY_OFF = no
MTK_AB_OTA_UPDATER = no
MTK_USERIMAGES_USE_F2FS = yes
MT6580_USE_FCHR_ENB_KEY = yes
