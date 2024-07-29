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

#ifndef __MT_REG_BASE
#define __MT_REG_BASE

#define BOOTROM_BASE (0x00000000)
#define BOOTSRAM_BASE (0x00100000)
#define IO_PHYS (0x10000000)

// APB Module cksys
#define CKSYS_BASE (0x10000000)
#define TOPCKGEN_BASE (0x10000000)

// APB Module infracfg_ao
#define INFRACFG_AO_BASE (0x10001000)

// APB Module iocfg_xx
#define IOCFG_RM_BASE (0x11C20000)
#define IOCFG_BM_BASE (0x11D10000)
#define IOCFG_BL_BASE (0x11D30000)
#define IOCFG_BR_BASE (0x11D40000)
#define IOCFG_LM_BASE (0x11E20000)
#define IOCFG_LB_BASE (0x11E70000)
#define IOCFG_RT_BASE (0x11EA0000)
#define IOCFG_LT_BASE (0x11F20000)
#define IOCFG_TL_BASE (0x11F30000)

#define PERICFG_BASE (0x10003000)

// APB Module dramc
#define DRAMC0_BASE (0x10230000)

// APB Module gpio
#define GPIO_BASE (0x10005000)

// APB Module sleep
#define SLEEP_BASE (0x10006000)

// APB Module dvfsrc
#define DVFSRC_BASE (0x10012000)

// APB Module toprgu
#define TOPRGU_BASE (0x10007000)

// APB Module apxgpt
#define APXGPT_BASE (0x10008000)

// APB Module rsvd
#define RSVD_BASE (0x10009000)

// APB Module sej
#define SEJ_BASE (0x1000A000)

// APB Module ap_cirq_eint
#define APIRQ_BASE (0x1000B000)

// APB Module smi
//#define SMI_COMMON_AO_BASE (0x10211000)

// APB Module pmic_wrap
#define PMIF_SPI_BASE    (0x10026000)
#define PMICSPI_MST_BASE (0x10028000)

// APB Module pmif for spmi
#define PMIF_SPMI_BASE	(0x10027000)
// APB Module spmimst
#define SPMI_MST_BASE	(0x10029000)

// APB Module device_apc_ao
#define DEVAPC_AO_BASE (0x1000E000)

// APB Module ddrphy
#define DDRPHY_BASE (0x10236000)

// APB Module kp
#define KP_BASE (0x10010000)

// APB Module DRAMC1_BASE
//#define DRAMC1_BASE (0x10011000)

// APB Module DDRPHY1_BASE
//#define DDRPHY1_BASE (0x10012000)


#define SECURITY_AO_BASE (0x1001a000)

// APB Module md32
//#define MD32_BASE (0x10058000)

// APB Module dbgapb
#define DBGAPB_BASE (0x0D000000)

// APB Module mcucfg
#define MCUCFG_BASE (0x0C530000)

// APB Module ca7mcucfg
//#define CA7MCUCFG_BASE (0x10200000)

// APB Module infracfg
#define INFRACFG_BASE (0x1020E000)

// APB Module sramrom
#define SRAMROM_BASE (0x10214000)

// APB Module emi
#define EMI_BASE (0x10219000)

// APB Module sys_cirq
#define SYS_CIRQ_BASE (0x10204000)

// APB Module mm_iommu
#define M4U_BASE (0x10220000)

// APB Module efusec
#define EFUSEC_BASE (0x11C10000)

// APB Module device_apc
#define DEVAPC_BASE (0x10207000)

// APB Module bus_dbg_tracker_cfg
#define BUS_DBG_BASE (0x10208000)

// APB Module apmixed
#define APMIXED_BASE (0x1000C000)

// APB Module fhctl
#define FHCTL_BASE (0x1000CE00)

// APB Module ccif
#define AP_CCIF0_BASE (0x10209000)

// APB Module ccif
#define MD_CCIF0_BASE (0x1020A000)

// APB Module gpio1
//#define GPIO1_BASE (0x1020C000)

// APB Module infra_mbist
#define INFRA_MBIST_BASE (0x1020D000)

// APB Module dramc_conf_nao
#define DRAMC_NAO_BASE (0x10234000)

// APB Module trng
#define TRNG_BASE (0x1020F000)

// APB Module gcpu
//#define GCPU_BASE (0x10210000)

// APB Module gcpu_ns
//#define GCPU_NS_BASE (0x10211000)

// APB Module gcpu_ns
#define GCE_BASE (0x10228000)

// APB Module dramc_conf_nao
//#define DRAMC1_NAO_BASE (0x1033C000)

// APB Module perisys_iommu
#define PERISYS_IOMMU_BASE (0x10220000)

// APB Module mipi_tx_config
#define MIPI_TX0_BASE (0x11E50000)
#define MIPI_TX1_BASE (0xffffffff)

// MIPI TX Config
#define MIPI_TX_CONFIG_BASE (0x11E50000)

// APB Module mipi_rx_ana_csi0
#define MIPI_RX_ANA_CSI0_BASE (0x10217000)

// APB Module mipi_rx_ana_csi1
#define MIPI_RX_ANA_CSI1_BASE (0x10218000)

// APB Module mipi_rx_ana_csi2
//#define MIPI_RX_ANA_CSI2_BASE (0x10219000)

// APB Module ca9
//#define CA9_BASE (0x10220000)

// APB Module gce
#define GCE_BASE (0x10228000)

// APB Module cq_dma
#define CQ_DMA_BASE (0x10212000)

// scp
#define SCP_BASE (0x10700000)

// adsp
#define ADSP_BASE (0x10800000)

// APB Module ap_dma
#define AP_DMA_BASE (0x11000000)

// APB Module auxadc
#define AUXADC_BASE (0x11001000)

// APB Module uart
#define AP_UART0_BASE (0x11002000)

// APB Module uart
#define AP_UART1_BASE (0x11003000)

// APB Module uart
//#define AP_UART2_BASE (0x11004000)

// APB Module pwm
#define PWM_BASE (0x11006000)

// APB Module spi
#define SPI1_BASE (0x11010000)

// APB Module therm_ctrl
#define THERM_CTRL_BASE (0x1100B000)

// APB Module btif
#define BTIF_BASE (0x1100C000)


// APB Module nfi
//#define NFI_BASE (0x1100D000)

// APB Module nfiecc
//#define NFIECC_BASE (0x1100E000)

// APB Module nli_arb
//#define NLI_ARB_BASE (0x1100F000)

// APB Module usb2
#define USB_BASE (0x11200000)

// APB Module usb_sif
#define USBSIF_BASE (0x11CC0000)

// APB Module audio
#define AUDIO_BASE (0x11210000)

#define MSDC0_TOP_BASE (0x11F50000)
#define MSDC1_TOP_BASE (0x11C70000)

// APB Module msdc
//#define MSDC_TOP_BASE (0x104D0000)

// APB Module msdc
#define MSDC0_BASE (0x11F60000)

// APB Module msdc
#define MSDC1_BASE (0x11F70000)

// APB Module msdc
#define MSDC2_BASE (0x11F80000)

// APB Module msdc
#define MSDC3_BASE (0x11260000)

// APB Module USB_1p
//#define ICUSB_BASE (0x11270000)

// APB Module ssusb_top
#define USB3_BASE (0x11200000)

// APB Module ssusb_top_sif
#define USB3_SIF_BASE (0x11E40000)

// APB Module ssusb_top_sif2
#define USB3_SIF2_BASE (0x11290000)

// APB Module mfg_top
#define MFGCFG_BASE (0x13000000)

// APB Module han
//#define HAN_BASE (0x13000000)

// APB Module mmsys_config
#define MMSYS_CONFIG_BASE (0x14000000)

// APB Module mdp_rdma
#define MDP_RDMA0_BASE (0x14001000)

// APB Module mdp_rdma
#define MDP_RDMA1_BASE (0x14002000)

// APB Module mdp_rdma
#define MDP_RDMA4_BASE (0x1400f000)

// APB Module mdp_rdma
#define MDP_RDMA5_BASE (0x1410f000)

// APB Module mdp_rsz
#define MDP_RSZ0_BASE (0x14003000)

// APB Module mdp_rsz
#define MDP_RSZ1_BASE (0x14004000)

// APB Module mdp_rsz
//#define MDP_RSZ2_BASE (0x14005000)

// APB Module mdp_rsz
#define MDP_RSZ4_BASE (0x14012000)

// APB Module mdp_rsz
#define MDP_RSZ5_BASE (0x14112000)

// APB Module disp_wdma
#define MDP_WDMA_BASE (0x14006000)

// APB Module mdp_wrot
#define MDP_WROT0_BASE (0x14005000)

// APB Module mdp_wrot
#define MDP_WROT1_BASE (0x14020000)

// APB Module mdp_tdshp
#define MDP_TDSHP0_BASE (0x14007000)

// APB Module mdp_tdshp
#define MDP_TDSHP1_BASE (0x14031000)

// APB Module mdp_aal
#define MDP_AAL5_BASE (0x14110000)

// APB Module mdp_tdshp
//#define MDP_CROP_BASE (0x1400b000)

// DISPSYS
#define OVL0_BASE (0x14005000)
#define OVL1_BASE (0x14100000)
#define DISP_OVL0_2L_BASE (0x14006000)
#define DISP_OVL2_2L_BASE (0x14014000)
#define DISP_OVL1_2L_BASE (0x14101000)
#define DISP_OVL3_2L_BASE (0x14102000)
#define DISP_RDMA0_BASE (0x14007000)
#define DISP_RDMA4_BASE (0x14015000)
#define DISP_RDMA1_BASE (0x14103000)
#define DISP_RDMA5_BASE (0x14105000)
#define DISP_WDMA0_BASE (0x14011000)
#define DISP_UFBC_WDMA0_BASE (0x14012000)
#define DISP_WDMA1_BASE (0x14106000)
#define DISP_SPLIT0_BASE (0xffffffff)
#define DSI0_BASE (0x14010000)
#define DSI1_BASE (0x1410e000)
#define DISP_MERGE0_BASE (0x14015000)
#define DISP_MERGE1_BASE (0x14115000)
#define MM_MUTEX_BASE (0x14001000)
#define DISP_DSC_BASE (0x1400f000)

#define MDP_RDMA4_BASE       (0x14017000)
#define MDP_HDR4_BASE        (0x14018000)
#define MDP_RSZ4_BASE        (0x14019000)
#define MDP_AAL4_BASE        (0x1401a000)
#define MDP_TDSHP4_BASE      (0x1401b000)
#define MDP_COLOR4_BASE      (0x1401c000)


// PQ and AAL
#define COLOR0_BASE (0x14009000)
#define COLOR1_BASE (0x14107000)
#define CCORR0_BASE  (0x1400a000)
#define CCORR1_BASE  (0x14108000)
#define DISP_AAL0_BASE (0x1400b000)
#define DISP_AAL1_BASE (0x14109000)
#define DISP_GAMMA0_BASE (0x1400c000)
#define DISP_GAMMA1_BASE (0x1410a000)
#define DITHER0_BASE (0x1400e000)
#define DITHER1_BASE (0x1410b000)
#define DISP_RSZ0_BASE (0x14008000)
#define DISP_RSZ1_BASE (0x1410c000)

// APB Module disp_dpi
#define DPI_BASE (0x14016000)
#define DPTX_BASE (0x14800000)

// APB Module disp_postmask
#define DISP_POSTMASK0_BASE (0x1400d000)
#define DISP_POSTMASK1_BASE (0x1410d000)

// APB Module disp_pwm
#define DISP_PWM0_BASE (0x1100E000)

// APB Module smi_larb0
#define SMI_LARB0_BASE (0x14003000)

// APB Module smi_larb5
#define SMI_LARB1_BASE (0x14004000)

// APB Module smi_larb
#define SMI_LARB2_BASE (0x16010000)

// APB Module smi
#define SMI_COMMON_BASE (0x14002000)

// APB Module smi_subcom0
#define SMI_SUBCOM0_BASE (0x14022000)

// APB Module smi_subcom1
#define SMI_SUBCOM1_BASE (0x14023000)

// APB Module smi_larb
#define SMI_LARB5_BASE (0x1502F000)

// APB Module fake_eng
//#define FAKE_ENG_BASE (0x15002000)

// APB Module imgsys
#define IMGSYS_BASE (0x15020000)

// APB Module cam1
#define CAM1_BASE (0x1A003000)

// APB Module cam2
#define CAM2_BASE (0x1A004000)

// APB Module cam3
#define CAM3_BASE (0x1A005000)

// APB Module cam4
#define CAM4_BASE (0x1A006000)

// APB Module camsv
#define CAMSV_BASE (0x1a050000)

// APB Module camsv_top
#define CAMSV_TOP_BASE (0x1a050000)

// APB Module csi2
#define CSI2_BASE (0x1A040000)

// APB Module seninf
#define SENINF_BASE (0x1A040000)

// APB Module seninf_tg
#define SENINF_TG_BASE (0x1A040000)

// APB Module seninf_top
#define SENINF_TOP_BASE (0x1A040000)

// APB Module seninf_mux
#define SENINF_MUX_BASE (0x1A040000)

// APB Module mipi_rx_config
#define MIPI_RX_CONFIG_BASE (0x10217000)

// APB Module scam
#define SCAM_BASE (0x1A044000)

// APB Module ncsi2
//#define NCSI2_BASE (0x15008000)

// APB Module ccir656
#define CCIR656_BASE (0x1A044000)

// APB Module n3d_ctl
//#define N3D_CTL_BASE (0x15008000)

// APB Module fdvt
#define FDVT_BASE (0x1502B000)

// APB Module vdecsys_config
#define VDEC_GCON_BASE (0x16000000)

// APB Module vdtop
#define VDEC_BASE (0x16020000)

// APB Module vdtop
#define VDTOP_BASE (0x16025000)

// APB Module vld
#define VLD_BASE (0x16020000)

// APB Module vld_top
//#define VLD_TOP_BASE (0x16021800)

// APB Module mc
#define MC_BASE (0x16021000)

// APB Module avc_vld
#define AVC_VLD_BASE (0x16022000)

// APB Module avc_mv
#define AVC_MV_BASE (0x16023000)

// APB Module vdec_pp
#define VDEC_PP_BASE (0x16024000)

// APB Module hevc_vld
#define HEVC_VLD_BASE (0x16028000)

// APB Module vp8_vld
#define VP8_VLD_BASE (0x16027800)

// APB Module vp6
#define VP6_BASE (0x16026000)

// APB Module vld2
#define VLD2_BASE (0x16026800)

// APB Module mc_vmmu
//#define MC_VMMU_BASE (0x16028000)

// APB Module pp_vmmu
//#define PP_VMMU_BASE (0x16029000)

// APB Module mjc_config
#define MJC_CONFIG_BASE (0x12000000)

// APB Module mjc_top
#define MJC_TOP_BASE (0x12001000)

// APB Module venc_config
#define VENC_GCON_BASE (0x17000000)

// APB Module smi_larb
#define SMI_LARB3_BASE (0x1A002000)

// APB Module venc
#define VENC_BASE (0x17020000)

// APB Module jpgenc
#define JPGENC_BASE (0x17030000)

// APB Module jpgdec
//#define JPGDEC_BASE (0x18004000)

// APB Module audiosys
//#define AUDIOSYS_BASE (0x11220000)

// rtc
#define RTC_BASE (0x2800)

//Marcos add for early porting
//#define SYSRAM_BASE (0x19000000)
#define GIC_DIST_BASE  (0x0C000000)
#define GIC_REDIS_BASE (0x0C040000)
//#define GIC_CPU_BASE  (CA9_BASE + 0x2000)
#if defined(MACH_FPGA)
// FPGA only
//#define DEVINFO_BASE (0x10001000)
#endif

/* hardware version register */
#define VER_BASE 0x08000000
#define APHW_CODE           (VER_BASE)
#define APHW_SUBCODE        (VER_BASE + 0x04)
#define APHW_VER            (VER_BASE + 0x08)
#define APSW_VER            (VER_BASE + 0x0C)

////////////////////////////////////////


/* Other define */
#define NON_BOOTABLE                0
#define RAW_BOOT                    1
#define FAT_BOOT                    2

#define CONFIG_STACKSIZE        (128*1024)    /* regular stack */

// xuecheng, define this because we use zlib for boot logo compression
#define CONFIG_ZLIB     1

/*MTK Memory layout configuration*/
#define MAX_NR_BANK    4

#define DRAM_PHY_ADDR   0x40000000

#define RIL_SIZE 0

#define CFG_RAMDISK_LOAD_ADDR           (DRAM_PHY_ADDR + 0x4000000)
#define CFG_BOOTIMG_LOAD_ADDR           (DRAM_PHY_ADDR + 0x8000)
#define CFG_BOOTARGS_ADDR               (DRAM_PHY_ADDR + 0x100)

#define CFG_FACTORY_NAME    "factory.img"
#define HAVE_LK_TEXT_MENU

#ifdef CONFIG_MTK_USB_UNIQUE_SERIAL
#define EFUSE_CTR_BASE      0x10206000  /* IO_PHYS + 0x01019000 */
//#define PDN_CTR           0xC0001020  /* IO_PHYS + 0x00001020 */
#define SERIAL_KEY_HI       (EFUSE_CTR_BASE + 0x0144)
#define SERIAL_KEY_LO       (EFUSE_CTR_BASE + 0x0140)
#endif

//ALPS00427972, implement the analog register formula
//Add here for eFuse, chip version checking -> analog register calibration
#define M_HW_RES3                       0x10009170
//#define M_HW_RES3_PHY                   IO_PHYS+M_HW_RES3
#define RG_USB20_TERM_VREF_SEL_MASK     0xE000      //0b 1110,0000,0000,0000     15~13
#define RG_USB20_CLKREF_REF_MASK        0x1C00      //0b 0001,1100,0000,0000     12~10
#define RG_USB20_VRT_VREF_SEL_MASK      0x0380      //0b 0000,0011,1000,0000     9~7
//ALPS00427972, implement the analog register formula

#endif








