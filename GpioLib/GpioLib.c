/*
 * GpioLib.c
 *
 *  Created on: Feb 19, 2019
 *      Author: javad
 */
#include "GpioLib.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

static void *g_p_mem;


void * gpio_init()
{
	int fd;
	void *p_mem;
	volatile uint32_t *gpio;    /* The registers in gpio-space are 32-bits wide. */
	unsigned int page_size;     /* Page-size from system, it reports 0x1000 here. */
	int j;
	page_size = sysconf(_SC_PAGESIZE);

	fd = open("/dev/mem", O_RDWR | O_SYNC);
	if(fd == -1)
	{
		/* Very likely if you forget to run this as root ... */
		perror("/dev/mem");
		return NULL;
	}

	p_mem = mmap(NULL, page_size * 2, PROT_READ | PROT_WRITE, MAP_SHARED, fd, BASE_ADDR);
	if(p_mem == NULL)
	{
		perror("mmap");
		close(fd);
		return NULL;
	}

	close(fd);
	return p_mem;
}
int
gpio_conf_pin(void *p_mem, const uint32_t i_port_name, const uint8_t i_pin_name
		, const uint8_t i_pin_mode)
{
	unsigned int offset;        /* offsets from 0x800, so need not be that big */
	volatile uint32_t *gpio;    /* The registers in gpio-space are 32-bits wide. */
	g_p_mem = gpio_init();
	offset = GPIO_REG_OFFSET + i_port_name;
	gpio = (volatile uint32_t *) ( (char *) (p_mem) + offset);

	*(gpio) &= ~(7 << i_pin_name);  /* Set SELECT to 000 for enable or input */

	switch(i_pin_mode)
	{
	case PIN_OUT:
		*(gpio) |= (1 << i_pin_name);   /* Set SELECT to 001 for output */
		break;
	case PIN_DISABLE:
		*(gpio) |= (7 << i_pin_name);
		break;
	default:/* As Default we set the pin as input */
		*(gpio) &= ~(7 << i_pin_name);  /* Set SELECT to 000 for enable or input */

	}

//	offset += 0x10;//PB_DATA_REG;
//
//	gpio = (volatile uint32_t *) ( (char *) (p_mem) + offset);
//	printf("GPIOs at %p\n", gpio);
//
//	while(1){
//		       *(gpio) &= (0x00);  /* Set bit 4 for PC4 to 0 */
//		//       usleep(50000);
//		       sleep(2);
//		       *(gpio) |= (0xFF);   /* Set bit 4 for PC4 to 1 */
//		       usleep(5000);
//		   }
//	   munmap(p_mem, page_size*2);
	return 0;
}

int gpio_read_pin(void *p_mem, const uint32_t i_port_name, const uint8_t i_pin_name)
{

	volatile uint32_t *gpio;    /* The registers in gpio-space are 32-bits wide. */
	unsigned int offset = 0;

	offset = GPIO_REG_OFFSET + i_port_name + 0x10;
	while(1){
		printf("Port out is : %u\n",*(gpio) & 0x00000001);
		sleep(1);

	}

	return 0;
}

int gpio_write_pin(void *p_mem, const uint32_t i_port_name,
		const uint8_t i_pin_name, const unsigned char i_pin_val )
{
	volatile uint32_t *gpio;    /* The registers in gpio-space are 32-bits wide. */
	unsigned int offset = 0;
	offset = GPIO_REG_OFFSET + i_port_name + 0x10;
	gpio = (volatile uint32_t *) ( (char *) (p_mem) + offset);
	*(gpio) &=~(1 << i_pin_name/4);
	*(gpio) |= (i_pin_val << i_pin_name/4);

	return 0;
}
