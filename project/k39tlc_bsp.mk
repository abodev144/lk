
LOCAL_DIR := $(GET_LOCAL_DIR)
TARGET := k39tlc_bsp
MODULES += app/mt_boot \
           dev/lcm
PMIC_CHIP := MT6357
ifeq ($(findstring PMIC_CHIP, $(strip $(DEFINES))),)
DEFINES += PMIC_CHIP_$(shell echo $(PMIC_CHIP) | tr '[a-z]' '[A-Z]')
endif
MTK_UFS_SUPPORT = no
MTK_EMMC_SUPPORT = yes
MTK_MLC_NAND_SUPPORT=no
MTK_TLC_NAND_SUPPORT=no
MTK_COMBO_NAND_SUPPORT =no
MNTL_SUPPORT = no
MTK_KERNEL_POWER_OFF_CHARGING = yes
MTK_SMI_SUPPORT = no
MTK_PUMP_EXPRESS_PLUS_SUPPORT := no
MTK_RT9458_SUPPORT := no
MTK_CHARGER_INTERFACE := yes
MTK_LCM_PHYSICAL_ROTATION = 0
CUSTOM_LK_LCM="u3a_st7701_fwvga_dsi_ykl"
MTK_SECURITY_SW_SUPPORT = yes
MTK_SEC_FASTBOOT_UNLOCK_SUPPORT = yes
MTK_VERIFIED_BOOT_SUPPORT = yes
CUSTOM_LK_USB_UNIQUE_SERIAL = yes
BOOT_LOGO := hd720
DEFINES += SERIAL_NUM_FROM_BARCODE=1
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
