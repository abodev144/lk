#
LOCAL_DIR := $(GET_LOCAL_DIR)
TARGET := k62v1_32_bsp
MODULES += app/mt_boot \
           dev/lcm
MTK_EMMC_SUPPORT = yes
MTK_MMC_COMBO_DRV = yes
MTK_EMMC_SUPPORT_OTP = yes
MTK_SMI_SUPPORT = yes
MTK_KERNEL_POWER_OFF_CHARGING = yes
DEFINES += MTK_NEW_COMBO_EMMC_SUPPORT
DEFINES += MTK_GPT_SCHEME_SUPPORT
MTK_CHARGER_NEW_ARCH := yes
MTK_PUMP_EXPRESS_PLUS_SUPPORT := yes
MTK_MT6370_PMU_CHARGER_SUPPORT := yes
MTK_MT6370_PMU_BLED_SUPPORT := yes
MTK_CHARGER_INTERFACE := yes
MTK_LCM_PHYSICAL_ROTATION = 0
CUSTOM_LK_LCM="nt35695B_fhd_dsi_vdo_auo_rt5081_hdp nt35695_fhd_dsi_vdo_truly_rt5081_hdp"
DEFINES += MTK_ROUND_CORNER_SUPPORT
#nt35595_fhd_dsi_cmd_truly_nt50358 = yes
#FASTBOOT_USE_G_ORIGINAL_PROTOCOL = yes
MTK_SECURITY_SW_SUPPORT = yes
MTK_VERIFIED_BOOT_SUPPORT = yes
MTK_SEC_FASTBOOT_UNLOCK_SUPPORT = yes
SPM_FW_USE_PARTITION = yes
BOOT_LOGO := hdplus
DEBUG := 2
#DEFINES += WITH_DEBUG_DCC=1
DEFINES += WITH_DEBUG_UART=1
#DEFINES += WITH_DEBUG_FBCON=1
CUSTOM_LK_USB_UNIQUE_SERIAL=no
MTK_TINYSYS_SCP_SUPPORT = yes
MTK_TINYSYS_SSPM_SUPPORT = yes
#DEFINES += NO_POWER_OFF=y
#DEFINES += FPGA_BOOT_FROM_LK=y
MTK_PROTOCOL1_RAT_CONFIG = C/Lf/Lt/W/T/G
MTK_GOOGLE_TRUSTY_SUPPORT = no
DEFINES += MTK_MT6370_PMU
MTK_EFUSE_WRITER_SUPPORT = no
MTK_SMC_ID_MGMT = yes
DEVELOP_STAGE = SB
MTK_LK_ENABLE_DCM = yes
MTK_MT22_MODE :=H2
MTK_PLATFORM_REVISED = MT6762
