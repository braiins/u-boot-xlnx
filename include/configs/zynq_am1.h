/*
 * (C) Copyright 2013 Xilinx, Inc.
 *
 * Configuration settings for the Xilinx Zynq ZC702 and ZC706 boards
 * See zynq-common.h for Zynq common configs
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_ZYNQ_DM1_H
#define __CONFIG_ZYNQ_DM1_H

#define CONFIG_SYS_NO_FLASH

#define CONFIG_CMD_UNZIP
#define CONFIG_CMD_SETEXPR

#define CONFIG_SYS_SDRAM_SIZE (1 * 1024 * 1024 * 1024)

#include <configs/zynq-common.h>

#endif /* __CONFIG_ZYNQ_DM1_H */
