#
LOCAL_DIR := $(GET_LOCAL_DIR)
TARGET := k39tv1_bsp_1g
MODULES += app/mt_boot \
           dev/lcm
PMIC_CHIP := MT6357
ifeq ($(findstring PMIC_CHIP, $(strip $(DEFINES))),)
DEFINES += PMIC_CHIP_$(shell echo $(PMIC_CHIP) | tr '[a-z]' '[A-Z]')
endif
MTK_UFS_SUPPORT = no
MTK_EMMC_SUPPORT = yes
MTK_MMC_COMBO_DRV = yes
MTK_KERNEL_POWER_OFF_CHARGING = yes
MTK_SMI_SUPPORT = yes
DEFINES += MTK_NEW_COMBO_EMMC_SUPPORT
DEFINES += MTK_GPT_SCHEME_SUPPORT
MTK_PUMP_EXPRESS_PLUS_SUPPORT := no
MTK_RT9458_SUPPORT := no
MTK_CHARGER_INTERFACE := yes
MTK_LCM_PHYSICAL_ROTATION = 0
CUSTOM_LK_LCM="u3a_st7701_fwvga_dsi_ykl"
#nt35595_fhd_dsi_cmd_truly_nt50358 = yes
#FASTBOOT_USE_G_ORIGINAL_PROTOCOL = yes
MTK_VERIFIED_BOOT_SUPPORT = no
MTK_SEC_FASTBOOT_UNLOCK_SUPPORT = yes
SPM_FW_USE_PARTITION = yes
BOOT_LOGO := hd720
DEFINES += MTK_LCM_PHYSICAL_ROTATION_HW
DEBUG := 2
#DEFINES += WITH_DEBUG_DCC=1
DEFINES += WITH_DEBUG_UART=1
#DEFINES += WITH_DEBUG_FBCON=1
CUSTOM_LK_USB_UNIQUE_SERIAL=no
MTK_TINYSYS_SCP_SUPPORT = no
MTK_TINYSYS_SSPM_SUPPORT = no
#DEFINES += NO_POWER_OFF=y
#DEFINES += FPGA_BOOT_FROM_LK=y
MTK_PROTOCOL1_RAT_CONFIG = Lf/Lt/W/G
MTK_GOOGLE_TRUSTY_SUPPORT = no
MCUPM_FW_USE_PARTITION = yes
MTK_DM_VERITY_OFF = no
MTK_DYNAMIC_CCB_BUFFER_GEAR_ID =3
MTK_USERIMAGES_USE_F2FS = yes
MTK_MRDUMP_ENABLE := no
MTK_AVB20_SUPPORT:=NO
AVB_SHA256_CRYPTO_HW_SUPPORT:=yes
MTK_AB_OTA_UPDATER = NO
