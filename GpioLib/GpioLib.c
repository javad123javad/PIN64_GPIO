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
void * gpio_init()
{
	int fd;
	void *p_mem;
	volatile uint32_t *gpio;    /* The registers in gpio-space are 32-bits wide. */
	unsigned int offset;        /* offsets from 0x800, so need not be that big */
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
int gpio_set_pin(const uint32_t i_port_name, const uint8_t i_pin_name
		, const uint8_t i_pin_mode)
{

	return 0;
}

