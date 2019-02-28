/*
 * GpioLib.h
 *
 *  Created on: Feb 19, 2019
 *      Author: javad
 */

#ifndef GPIOLIB_H_
#define GPIOLIB_H_
#include <stdint.h>
/* Macro Function */
#define __locate_base_addr(BASE_ADDR, CFG_NUM)	(BASE_ADDR) + (4*(CFG_NUM))
struct PIN_CFG
{
	unsigned char BASE_ADDR;
	unsigned char CFG_REG;
};
#define BASE_ADDR 0x01c20000
#define GPIO_REG_OFFSET 0x800
/* PIN Status */
#define PIN_IN		0x00000000
#define PIN_OUT		0x00000001
#define PIN_DISABLE	0x00000007
/* Pull resistor status */
#define PULL_DISABLE	0x00
#define PULL_UP			0x01
#define PULL_DOWN		0x02
/* PORTB Base Address */
#define PB0_SELECT 	0
#define PB1_SELECT 	4
#define PB2_SELECT 	8
#define PB3_SELECT 	12
#define PB4_SELECT 	16
#define PB5_SELECT 	20
#define PB6_SELECT	24
#define PB7_SELECT 	28
#define PB8_SELECT 	0
#define PB9_SELECT 	4

#define PORTB			0x24
#define PB_CFG0_REG		__locate_base_addr(PORTB, 0)//0x24
#define PB_CFG1_REG		__locate_base_addr(PORTB, 1)//0x24 + 0x04
#define PB_CFG2_REG		__locate_base_addr(PORTB, 2)//0x24 + 0x08
#define PB_CFG3_REG		__locate_base_addr(PORTB, 3)//0x24 + 0x0c
#define PB_DATA_REG		__locate_base_addr(PORTB, 4)//0x24 + 0x10
#define PB_PULL0_REG	__locate_base_addr(PORTB, 7)//0x24 + 0x1c
#define PB_PULL1_REG	__locate_base_addr(PORTB, 8)//0x24+  0x20
/* End of PIN Register definition */
void * gpio_init();

int gpio_conf_pin(void *p_mem, const uint32_t i_port_name, const uint8_t i_pin_name
		, const uint8_t i_pin_mode);
int gpio_read_pin(void *p_mem, const uint32_t i_port_name, const uint8_t i_pin_name);
int gpio_write_pin(void *p_mem, const uint32_t i_port_name, const uint8_t i_pin_name, const unsigned char i_pin_val);

#endif /* GPIOLIB_H_ */
