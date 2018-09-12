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

#define CONFIG_SYS_SDRAM_SIZE (512 * 1024 * 1024)

#define CONFIG_XILINX_GPIO

#define GPIO_INIT \
	"led_green=2\0" \
	"led_red=3\0" \
	"button_ip=28\0" \
	"gpio_output_addr=0x41210000\0" \
	"gpio_output_width=0x1c\0" \
	"gpio_input_addr=0x41230000\0" \
	"gpio_input_width=0x1\0" \
	"gpio_init=" \
		"gpio alloc ${gpio_output_addr} ${gpio_output_width} output && " \
		"gpio alloc ${gpio_input_addr} ${gpio_input_width} input\0"

#define GPIO_INIT_RUN \
	"run gpio_init && "

#include <configs/zynq-common.h>

#endif /* __CONFIG_ZYNQ_DM1_H */
