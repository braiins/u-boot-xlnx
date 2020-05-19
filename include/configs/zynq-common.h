/*
 * (C) Copyright 2012 Michal Simek <monstr@monstr.eu>
 * (C) Copyright 2013 Xilinx, Inc.
 *
 * Common configuration options for all Zynq boards.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_ZYNQ_COMMON_H
#define __CONFIG_ZYNQ_COMMON_H

/* CPU clock */
#ifndef CONFIG_CPU_FREQ_HZ
# define CONFIG_CPU_FREQ_HZ	800000000
#endif

/* Cache options */
#define CONFIG_CMD_CACHE
#define CONFIG_SYS_CACHELINE_SIZE	32

#define CONFIG_SYS_L2CACHE_OFF
#ifndef CONFIG_SYS_L2CACHE_OFF
# define CONFIG_SYS_L2_PL310
# define CONFIG_SYS_PL310_BASE		0xf8f02000
#endif

#define ZYNQ_SCUTIMER_BASEADDR		0xF8F00600
#define CONFIG_SYS_TIMERBASE		ZYNQ_SCUTIMER_BASEADDR
#define CONFIG_SYS_TIMER_COUNTS_DOWN
#define CONFIG_SYS_TIMER_COUNTER	(CONFIG_SYS_TIMERBASE + 0x4)

/* Serial drivers */
#define CONFIG_BAUDRATE		115200
/* The following table includes the supported baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE  \
	{300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400}

#define CONFIG_ARM_DCC
#define CONFIG_ZYNQ_SERIAL

/* Ethernet driver */
#if defined(CONFIG_ZYNQ_GEM)
# define CONFIG_MII
# define CONFIG_SYS_FAULT_ECHO_LINK_DOWN
# define CONFIG_PHY_MARVELL
# define CONFIG_PHY_REALTEK
# define CONFIG_BOOTP_SERVERIP
# define CONFIG_BOOTP_BOOTPATH
# define CONFIG_BOOTP_GATEWAY
# define CONFIG_BOOTP_HOSTNAME
# define CONFIG_BOOTP_MAY_FAIL
#endif

/* SPI */
#ifdef CONFIG_ZYNQ_SPI
# define CONFIG_CMD_SF
#endif

/* QSPI */
#ifdef CONFIG_ZYNQ_QSPI
# define CONFIG_SF_DEFAULT_SPEED	30000000
# define CONFIG_SPI_FLASH_ISSI
# define CONFIG_CMD_SF
#endif

/* NOR */
#ifndef CONFIG_SYS_NO_FLASH
# define CONFIG_SYS_FLASH_BASE		0xE2000000
# define CONFIG_SYS_FLASH_SIZE		(16 * 1024 * 1024)
# define CONFIG_SYS_MAX_FLASH_BANKS	1
# define CONFIG_SYS_MAX_FLASH_SECT	512
# define CONFIG_SYS_FLASH_ERASE_TOUT	1000
# define CONFIG_SYS_FLASH_WRITE_TOUT	5000
# define CONFIG_FLASH_SHOW_PROGRESS	10
# define CONFIG_SYS_FLASH_CFI
# undef CONFIG_SYS_FLASH_EMPTY_INFO
# define CONFIG_FLASH_CFI_DRIVER
# undef CONFIG_SYS_FLASH_PROTECTION
# define CONFIG_SYS_FLASH_USE_BUFFER_WRITE
#endif

/* MMC */
#if defined(CONFIG_ZYNQ_SDHCI)
# define CONFIG_MMC
# define CONFIG_GENERIC_MMC
# define CONFIG_SDHCI
# define CONFIG_CMD_MMC
# define CONFIG_ZYNQ_SDHCI_MAX_FREQ	52000000
#endif

#ifdef CONFIG_ZYNQ_USB
# define CONFIG_USB_EHCI
# define CONFIG_CMD_USB
# define CONFIG_USB_STORAGE
# define CONFIG_USB_EHCI_ZYNQ
# define CONFIG_USB_ULPI_VIEWPORT
# define CONFIG_USB_ULPI
# define CONFIG_EHCI_IS_TDI
# define CONFIG_USB_MAX_CONTROLLER_COUNT	2

# define CONFIG_CI_UDC           /* ChipIdea CI13xxx UDC */
# define CONFIG_USB_GADGET
# define CONFIG_USB_GADGET_DUALSPEED
# define CONFIG_USB_GADGET_DOWNLOAD
# define CONFIG_SYS_DFU_DATA_BUF_SIZE	0x600000
# define DFU_DEFAULT_POLL_TIMEOUT	300
# define CONFIG_USB_FUNCTION_DFU
# define CONFIG_DFU_RAM
# define CONFIG_USB_GADGET_VBUS_DRAW	2
# define CONFIG_G_DNL_VENDOR_NUM	0x03FD
# define CONFIG_G_DNL_PRODUCT_NUM	0x0300
# define CONFIG_G_DNL_MANUFACTURER	"Xilinx"
# define CONFIG_USB_GADGET
# define CONFIG_USB_CABLE_CHECK
# define CONFIG_CMD_DFU
# define CONFIG_CMD_THOR_DOWNLOAD
# define CONFIG_USB_FUNCTION_THOR
# define DFU_ALT_INFO_RAM \
	"dfu_ram_info=" \
	"set dfu_alt_info " \
	"${kernel_image} ram 0x3000000 0x500000\\\\;" \
	"${devicetree_image} ram 0x2A00000 0x20000\\\\;" \
	"${ramdisk_image} ram 0x2000000 0x600000\0" \
	"dfu_ram=run dfu_ram_info && dfu 0 ram 0\0" \
	"thor_ram=run dfu_ram_info && thordown 0 ram 0\0"

# if defined(CONFIG_ZYNQ_SDHCI)
#  define CONFIG_DFU_MMC
#  define DFU_ALT_INFO_MMC \
	"dfu_mmc_info=" \
	"set dfu_alt_info " \
	"${kernel_image} fat 0 1\\\\;" \
	"${devicetree_image} fat 0 1\\\\;" \
	"${ramdisk_image} fat 0 1\0" \
	"dfu_mmc=run dfu_mmc_info && dfu 0 mmc 0\0" \
	"thor_mmc=run dfu_mmc_info && thordown 0 mmc 0\0"

#  define DFU_ALT_INFO	\
	DFU_ALT_INFO_RAM \
	DFU_ALT_INFO_MMC
# else
#  define DFU_ALT_INFO	\
	DFU_ALT_INFO_RAM
# endif
#endif

#if !defined(DFU_ALT_INFO)
# define DFU_ALT_INFO
#endif

#if defined(CONFIG_ZYNQ_SDHCI) || defined(CONFIG_ZYNQ_USB)
# define CONFIG_SUPPORT_VFAT
# define CONFIG_CMD_FAT
# define CONFIG_CMD_EXT2
# define CONFIG_FAT_WRITE
# define CONFIG_DOS_PARTITION
# define CONFIG_CMD_EXT4
# define CONFIG_CMD_EXT4_WRITE
# define CONFIG_CMD_FS_GENERIC
#endif

/* NAND */
#ifdef CONFIG_NAND_ZYNQ
# define CONFIG_CMD_NAND
# define CONFIG_CMD_NAND_LOCK_UNLOCK
# define CONFIG_SYS_MAX_NAND_DEVICE 1
# define CONFIG_SYS_NAND_SELF_INIT
# define CONFIG_SYS_NAND_ONFI_DETECTION
# define CONFIG_MTD_DEVICE
# define CONFIG_SPL_NAND_SUPPORT
# define CONFIG_SPL_NAND_DRIVERS
# define CONFIG_SPL_NAND_BOOT
# define CONFIG_SYS_NAND_U_BOOT_OFFS	0x00080000
# define CONFIG_SYS_NAND_CHIPSIZE		0x10000000
# define CONFIG_SYS_NAND_PAGE_SIZE		2048
# define CONFIG_SYS_NAND_PAGE_COUNT		64
# define CONFIG_SYS_NAND_OOBSIZE		64
# define CONFIG_SYS_NAND_BLOCK_SIZE		0x20000
# define CONFIG_SYS_NAND_BAD_BLOCK_POS	0x0
# define CONFIG_SYS_NAND_ADDR_CYCLES	35 /* ROW: 3, COL: 2 */
#endif

#if defined(CONFIG_ZYNQ_I2C0) || defined(CONFIG_ZYNQ_I2C1)
#define CONFIG_SYS_I2C_ZYNQ
#endif

/* I2C */
#if defined(CONFIG_SYS_I2C_ZYNQ)
# define CONFIG_CMD_I2C
# define CONFIG_SYS_I2C
# define CONFIG_SYS_I2C_ZYNQ_SPEED		100000
# define CONFIG_SYS_I2C_ZYNQ_SLAVE		0
#endif

/* EEPROM */
#ifdef CONFIG_ZYNQ_EEPROM
# define CONFIG_CMD_EEPROM
# define CONFIG_SYS_I2C_EEPROM_ADDR_LEN		1
# define CONFIG_SYS_I2C_EEPROM_ADDR		0x54
# define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	4
# define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	5
# define CONFIG_SYS_EEPROM_SIZE			1024 /* Bytes */
#endif

/* Total Size of Environment Sector */
#define CONFIG_ENV_SIZE			(128 << 10)

/* Allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/* Environment */
#ifndef CONFIG_ENV_IS_NOWHERE
# ifndef CONFIG_SYS_NO_FLASH
/* Environment in NOR flash */
#  define CONFIG_ENV_IS_IN_FLASH
# elif defined(CONFIG_NAND_ZYNQ)
/* Environment in NAND flash */
#  define CONFIG_ENV_IS_IN_NAND
# elif defined(CONFIG_ZYNQ_QSPI)
/* Environment in Serial Flash */
#  define CONFIG_ENV_IS_IN_SPI_FLASH
# elif defined(CONFIG_SYS_NO_FLASH)
#  define CONFIG_ENV_IS_NOWHERE
# endif

# define CONFIG_ENV_SECT_SIZE		CONFIG_ENV_SIZE
# define CONFIG_ENV_OFFSET		0x700000
# define CONFIG_ENV_OFFSET_REDUND	(CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE)
#endif

#define CONFIG_SYS_REDUNDAND_ENVIRONMENT

/* MTD parts support */
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define MTDIDS_DEFAULT \
	"nand0=pl35x-nand"
#define MTDPARTS_DEFAULT \
	"mtdparts=pl35x-nand:" \
		"512k(boot)," \
		"2560k(uboot)," \
		"2m(fpga1)," \
		"2m(fpga2)," \
		"512k(uboot_env)," \
		"512k(miner_cfg)," \
		"22m(recovery)," \
		"95m(firmware1)," \
		"95m(firmware2)"

/* UBI support */
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#define CONFIG_RBTREE
#define CONFIG_LZO

#define CONFIG_UENV_ADDR	"0x2100000"
#define CONFIG_UENV_SIZE	"0x1000"

#ifndef GPIO_INIT
#define GPIO_INIT
#endif

#ifndef GPIO_INIT_RUN
#define GPIO_INIT_RUN
#endif

/* Default environment */
#define CONFIG_EXTRA_ENV_SETTINGS \
	"recovery_delay=0x3\0" \
	"factory_reset_delay=0xa\0" \
	"factory_reset=yes\0" \
	"first_boot=yes\0" \
	"firmware=1\0" \
	"load_addr=0x2000000\0" \
	"fdt_high=0x7FFFFFF\0" \
	"initrd_high=0x7FFFFFF\0" \
	"miner_cfg_size=0x20000\0" \
	"recovery_size=0x800000\0" \
	"bitstream_recovery_off=0x1C00000\0" \
	"bitstream_addr=0x2100000\0" \
	"bitstream_size=0x100000\0" \
	"boot_recovery_off=0x1D00000\0" \
	"boot_recovery_size=0x20000\0" \
	"boot_addr=0x2040000\0" \
	"boot_size=0x40000\0" \
	"uboot_recovery_off=0x1D20000\0" \
	"uboot_recovery_size=0xE0000\0" \
	"uboot_addr=0x2200000\0" \
	"uboot_size=0x200000\0" \
	GPIO_INIT \
	"uenv_load=" \
		"load mmc 0 ${load_addr} ${bootenv} && " \
		"echo Loaded environment from ${bootenv} && " \
		"env import -t ${load_addr} ${filesize}\0" \
	"uenv_reset=echo Resetting miner configuration... && " \
		"nand erase.part uboot_env && " \
		"reset\0" \
	"firmware_select=" \
		"if test x${firmware} = x1; then " \
			"setenv bitstream fpga1 && " \
			"setenv firmware_name firmware1 && " \
			"setenv firmware_mtd 7; " \
		"else " \
			"setenv bitstream fpga2 && " \
			"setenv firmware_name firmware2 && " \
			"setenv firmware_mtd 8; " \
		"fi\0" \
	"auto_recovery=" \
		"if test x${upgrade_stage} = x0; then " \
			"echo Trying to boot system after upgrade... && " \
			"setenv upgrade_stage 1 && " \
			"saveenv; " \
		"elif test x${upgrade_stage} = x1; then " \
			"echo Revert to previous firmware after unsuccessful upgrade... && " \
			"if test x${firmware} = x1; then " \
				"setenv firmware 2; " \
			"else " \
				"setenv firmware 1; " \
			"fi; " \
			"setenv upgrade_stage && " \
			"setenv first_boot && " \
			"saveenv && " \
			"reset; " \
		"else " \
			"exit 0; " \
		"fi\0" \
	"bootloaders_repair=" \
		"do_reset=no && " \
		"nand read ${load_addr} ${boot_recovery_off} ${boot_recovery_size} && " \
		"mw.b ${boot_addr} 0xff ${boot_size} && " \
		"unzip ${load_addr} ${boot_addr} && " \
		"nand read ${load_addr} boot ${boot_size} && " \
		"if cmp.b ${load_addr} ${boot_addr} ${boot_size}; then true; else " \
			"echo Restoring factory SPL... && " \
			"nand erase.part boot && " \
			"nand write ${boot_addr} boot ${boot_size} && " \
			"do_reset=yes; " \
		"fi; " \
		"nand read ${load_addr} ${uboot_recovery_off} ${uboot_recovery_size} && " \
		"mw.b ${uboot_addr} 0xff ${uboot_size} && " \
		"unzip ${load_addr} ${uboot_addr} && " \
		"nand read ${load_addr} uboot ${uboot_size} && " \
		"if cmp.b ${load_addr} ${uboot_addr} ${uboot_size}; then true; else " \
			"echo Restoring factory U-Boot... && " \
			"nand erase.part uboot && " \
			"nand write ${uboot_addr} uboot ${uboot_size} && " \
			"nand erase.part uboot_env; " \
			"do_reset=yes; " \
		"fi; " \
		"test x${do_reset} = xyes && reset; " \
		"exit 0\0" \
	"nandboot_init=echo Running factory reset... && " \
		"run bootloaders_repair && " \
		"env default -a && " \
		"if run uenv_load; then " \
			"env export -s "CONFIG_UENV_SIZE" -t "CONFIG_UENV_ADDR" sd_boot sd_images && " \
			"env default -a && " \
			"env import -t "CONFIG_UENV_ADDR" "CONFIG_UENV_SIZE" ; " \
		"fi; " \
		"nand read ${load_addr} miner_cfg ${miner_cfg_size} && " \
		"env import -c ${load_addr} ${miner_cfg_size} && " \
		"env set nandboot \"${nandboot_default}\" && " \
		"env delete nandboot_init nandboot_default && " \
		"saveenv && " \
		"run nandboot_recovery\0" \
	"nandboot_recovery=echo Running recovery process... && " \
		"test -n ${recovery_mtdparts} || setenv recovery_mtdparts ${mtdparts}; " \
		"setenv bootargs console=ttyPS0,115200 root=/dev/ram0 r rootfstype=squashfs ${recovery_mtdparts} earlyprintk && " \
		"nand read ${load_addr} ${bitstream_recovery_off} ${bitstream_size} && " \
		"unzip ${load_addr} ${bitstream_addr} && " \
		"fpga loadb 0 ${bitstream_addr} ${bitstream_size} && " \
		"nand read ${load_addr} recovery ${recovery_size} && " \
		"bootm ${load_addr}\0" \
	"nandboot_mode_select=" \
		"count=0; " \
		"while gpio input ${button_ip}; do " \
			"sleep 1; " \
			"setexpr count ${count} + 1; " \
			"itest ${count} >= ${recovery_delay} && gpio toggle ${led_green}; " \
			"if itest ${count} >= ${factory_reset_delay}; then " \
				"gpio set ${led_green}; " \
				"gpio set ${led_red}; " \
				"run uenv_reset; " \
			"fi; " \
		"done; " \
		"gpio set ${led_green}; " \
		"itest ${count} >= ${recovery_delay} && run nandboot_recovery; " \
		"gpio clear ${led_green}; " \
		"exit 0\0" \
	"nandboot_default=echo Copying FIT from NAND flash to RAM... && " \
		"if test x${recovery} = xyes; then " \
			"recovery=${recovery}; " \
			"recovery_mtdparts=${recovery_mtdparts}; " \
			"env set recovery; " \
			"env set recovery_mtdparts; " \
			"saveenv; " \
		"fi; " \
		"test x${first_boot} != xyes && run uenv_load; " \
		"test x${factory_reset} = xyes && run uenv_reset; " \
		"test x${sd_boot} = xyes && run sdboot; " \
		"test x${recovery} = xyes && run nandboot_recovery; " \
		"run firmware_select && " \
		"run auto_recovery && " \
		"setenv bootargs console=ttyPS0,115200 noinitrd ubi.mtd=${firmware_mtd} ubi.block=0,1 root=/dev/ubiblock0_1 r rootfstype=squashfs rootwait ${mtdparts} earlyprintk && " \
		"nand read ${load_addr} ${bitstream} ${bitstream_size} && " \
		"unzip ${load_addr} ${bitstream_addr} && " \
		"fpga loadb 0 ${bitstream_addr} ${bitstream_size} && " \
		GPIO_INIT_RUN \
		"run nandboot_mode_select && " \
		"ubi part ${firmware_name} && " \
		"ubi read ${load_addr} kernel && " \
		"gpio set ${led_green}; " \
		"bootm ${load_addr}\0" \
	"nandboot=run nandboot_init\0" \
	"fit_image=fit.itb\0" \
	"fpga_image=system.bit.gz\0" \
	"bootenv=uEnv.txt\0" \
	"sdboot=echo Copying FIT from SD to RAM... && " \
		"setenv recovery_mtdparts ${mtdparts}"SD_MTDPARTS_SUFFIX"; " \
		"run uenv_load; " \
		"test -n ${bootargs} || setenv bootargs console=ttyPS0,115200 root=/dev/ram0 r rootfstype=squashfs ${recovery_mtdparts} earlyprintk; " \
		"if test -n ${sd_uenvcmd}; then " \
			"echo Running sd_uenvcmd... && " \
			"run sd_uenvcmd; " \
		"fi; " \
		"load mmc 0 ${load_addr} ${fpga_image} && " \
		"unzip ${load_addr} ${bitstream_addr} && " \
		"fpga loadb 0 ${bitstream_addr} ${bitstream_size} && " \
		GPIO_INIT_RUN \
		"load mmc 0 ${load_addr} ${fit_image} && " \
		"gpio set ${led_green}; " \
		"bootm ${load_addr}\0" \
	"mtdids=" MTDIDS_DEFAULT "\0" \
	"mtdparts=" MTDPARTS_DEFAULT "\0" \
	DFU_ALT_INFO

#define CONFIG_BOOTCOMMAND		"run $modeboot"
#define CONFIG_BOOTDELAY		1 /* -1 to Disable autoboot */
#define CONFIG_SYS_LOAD_ADDR		0 /* default? */

/* Miscellaneous configurable options */
#define CONFIG_SYS_HUSH_PARSER

#define CONFIG_CMDLINE_EDITING
#define CONFIG_AUTO_COMPLETE
#define CONFIG_BOARD_LATE_INIT
#define CONFIG_DISPLAY_BOARDINFO
#define CONFIG_SYS_LONGHELP
#define CONFIG_CLOCKS
#define CONFIG_CMD_CLK
#define CONFIG_SYS_MAXARGS		32 /* max number of command args */
#define CONFIG_SYS_CBSIZE		256 /* Console I/O Buffer Size */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)

/* Physical Memory map */
#define CONFIG_SYS_TEXT_BASE		0x4000000

#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE		0

#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_SDRAM_BASE + 0x1000)

#define CONFIG_SYS_MALLOC_LEN		0x1400000
#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_INIT_RAM_SIZE	CONFIG_SYS_MALLOC_LEN
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_INIT_RAM_ADDR + \
					CONFIG_SYS_INIT_RAM_SIZE - \
					GENERATED_GBL_DATA_SIZE)

/* Enable the PL to be downloaded */
#define CONFIG_FPGA
#define CONFIG_FPGA_XILINX
#define CONFIG_FPGA_ZYNQPL
#define CONFIG_CMD_FPGA_LOADMK
#define CONFIG_CMD_FPGA_LOADP
#define CONFIG_CMD_FPGA_LOADBP
#define CONFIG_CMD_FPGA_LOADFS

/* Open Firmware flat tree */
#define CONFIG_OF_LIBFDT

/* FIT support */
#define CONFIG_IMAGE_FORMAT_LEGACY /* enable also legacy image format */

/* FDT support */
#define CONFIG_DISPLAY_BOARDINFO_LATE

/* Extend size of kernel image for uncompression */
#define CONFIG_SYS_BOOTM_LEN	(60 * 1024 * 1024)

/* Boot FreeBSD/vxWorks from an ELF image */
#define CONFIG_SYS_MMC_MAX_DEVICE	1

#define CONFIG_SYS_LDSCRIPT  "arch/arm/mach-zynq/u-boot.lds"

/* Commands */
#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_MII
#define CONFIG_CMD_TFTPPUT

/* SPL part */
#define CONFIG_CMD_SPL
#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_LIBGENERIC_SUPPORT
#define CONFIG_SPL_SERIAL_SUPPORT
#define CONFIG_SPL_BOARD_INIT
#define CONFIG_SPL_RAM_DEVICE

#define CONFIG_SPL_LDSCRIPT	"arch/arm/mach-zynq/u-boot-spl.lds"

/* MMC support */
#ifdef CONFIG_ZYNQ_SDHCI
#define CONFIG_SPL_MMC_SUPPORT
#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR 0x300 /* address 0x60000 */
#define CONFIG_SYS_U_BOOT_MAX_SIZE_SECTORS      0x200 /* 256 KB */
#define CONFIG_SYS_MMCSD_FS_BOOT_PARTITION     1
#define CONFIG_SPL_LIBDISK_SUPPORT
#define CONFIG_SPL_FAT_SUPPORT
#ifdef CONFIG_OF_SEPARATE
# define CONFIG_SPL_FS_LOAD_PAYLOAD_NAME     "u-boot-dtb.img"
#else
# define CONFIG_SPL_FS_LOAD_PAYLOAD_NAME     "u-boot.img"
#endif
#endif

/* Disable dcache for SPL just for sure */
#ifdef CONFIG_SPL_BUILD
#define CONFIG_SYS_DCACHE_OFF
#undef CONFIG_FPGA
#endif

/* Address in RAM where the parameters must be copied by SPL. */
#define CONFIG_SYS_SPL_ARGS_ADDR	0x10000000

#define CONFIG_SPL_FS_LOAD_ARGS_NAME		"system.dtb"
#define CONFIG_SPL_FS_LOAD_KERNEL_NAME		"uImage"

/* Not using MMC raw mode - just for compilation purpose */
#define CONFIG_SYS_MMCSD_RAW_MODE_ARGS_SECTOR	0
#define CONFIG_SYS_MMCSD_RAW_MODE_ARGS_SECTORS	0
#define CONFIG_SYS_MMCSD_RAW_MODE_KERNEL_SECTOR	0

/* qspi mode is working fine */
#ifdef CONFIG_ZYNQ_QSPI
#define CONFIG_SPL_SPI_SUPPORT
#define CONFIG_SPL_SPI_LOAD
#define CONFIG_SPL_SPI_FLASH_SUPPORT
#define CONFIG_SYS_SPI_U_BOOT_OFFS	0x100000
#define CONFIG_SYS_SPI_ARGS_OFFS	0x200000
#define CONFIG_SYS_SPI_ARGS_SIZE	0x80000
#define CONFIG_SYS_SPI_KERNEL_OFFS	(CONFIG_SYS_SPI_ARGS_OFFS + \
					CONFIG_SYS_SPI_ARGS_SIZE)
#endif

/* for booting directly linux */
/* #define CONFIG_SPL_OS_BOOT */

/* SP location before relocation, must use scratch RAM */
#define CONFIG_SPL_TEXT_BASE	0x0

/* 3 * 64kB blocks of OCM - one is on the top because of bootrom */
#define CONFIG_SPL_MAX_SIZE	0x30000

/* The highest 64k OCM address */
#define OCM_HIGH_ADDR	0xffff0000

/* On the top of OCM space */
#define CONFIG_SYS_SPL_MALLOC_START	OCM_HIGH_ADDR
#define CONFIG_SYS_SPL_MALLOC_SIZE	0x2000

/*
 * SPL stack position - and stack goes down
 * 0xfffffe00 is used for putting wfi loop.
 * Set it up as limit for now.
 */
#define CONFIG_SPL_STACK	0xfffffe00

/* BSS setup */
#define CONFIG_SPL_BSS_START_ADDR	0x100000
#define CONFIG_SPL_BSS_MAX_SIZE		0x100000

#define CONFIG_SYS_UBOOT_START	CONFIG_SYS_TEXT_BASE


#endif /* __CONFIG_ZYNQ_COMMON_H */
