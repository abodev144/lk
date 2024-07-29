#
LOCAL_DIR := $(GET_LOCAL_DIR)
TARGET := k71v1_64_bsp
MODULES += app/mt_boot \
           dev/lcm
MTK_EMMC_SUPPORT = yes
MTK_UFS_SUPPORT = yes
MTK_UFS_OTP = yes
MTK_KERNEL_POWER_OFF_CHARGING = yes
MTK_SMI_SUPPORT = yes
DEFINES += MTK_NEW_COMBO_EMMC_SUPPORT
DEFINES += MTK_GPT_SCHEME_SUPPORT
MTK_CHARGER_NEW_ARCH := yes
MTK_PUMP_EXPRESS_PLUS_SUPPORT := yes
MTK_CHARGER_INTERFACE := yes
MTK_MT6370_PMU_CHARGER_SUPPORT := yes
MTK_MT6370_PMU_BLED_SUPPORT := yes
MTK_LCM_PHYSICAL_ROTATION = 0
CUSTOM_LK_LCM="vtdr6110_fhdp_dsi_vdo_oled"
#nt35595_fhd_dsi_cmd_truly_nt50358 = yes
MTK_VERIFIED_BOOT_SUPPORT = no
MTK_SEC_FASTBOOT_UNLOCK_SUPPORT = yes
SPM_FW_USE_PARTITION = yes
BOOT_LOGO := fhdplus2400
DEBUG := 2
#DEFINES += WITH_DEBUG_DCC=1
DEFINES += WITH_DEBUG_UART=1
#DEFINES += WITH_DEBUG_FBCON=1
CUSTOM_LK_USB_UNIQUE_SERIAL=no
MTK_TINYSYS_SCP_SUPPORT = yes
MTK_PROTOCOL1_RAT_CONFIG = C/Lf/Lt/W/T/G
MTK_GOOGLE_TRUSTY_SUPPORT=no
DEFINES += MTK_MT6370_PMU
DEVELOP_STAGE = SB
MTK_TINYSYS_SSPM_SUPPORT = yes
MTK_VPU_SUPPORT = yes
MTK_DM_VERITY_OFF = no
MTK_DYNAMIC_CCB_BUFFER_GEAR_ID =
MTK_AVB20_SUPPORT:=yes
MTK_AB_OTA_UPDATER = yes
MTK_ENABLE_GENIEZONE=yes
