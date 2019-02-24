/*
 * I2CLib.c
 *
 *  Created on: Feb 15, 2019
 *      Author: javad
 */

#include "I2CLib.h"
#include "DbgLib.h"
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
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

#define BASE_ADDR 0x01c20000
#define GPIO_REG_OFFSET 0x800
int i2c_init()
{
	int		i2c_fd = 0;
	int 	i2c_adpt = 1;
	char 	i2c_name[32] = {0};
	char	buf[4] = {0};
	int fRet = 0;
	sprintf(i2c_name,"/dev/i2c-%d", i2c_adpt);

	i2c_fd = open(i2c_name, O_RDWR);
	if(i2c_fd < 0)
	{
		Debug(LOG_ERR,"I2C: %s: %s",i2c_name, strerror(errno));
		return errno;
	}
	 int addr = 0x40; /* The I2C address */

	  if (ioctl(i2c_fd, I2C_SLAVE, addr) < 0) {
	    /* ERROR HANDLING; you can check errno to see what went wrong */
			Debug(LOG_ERR,"I2C: %s: %s ioctl Len:%d",i2c_name, strerror(errno), fRet);

	  }

	buf[0] = DISP_ON;
	buf[1] = 0;
	fRet = write(i2c_fd, buf, 1);
	Debug(LOG_ERR,"I2C: %s: %s Write Len:%d",i2c_name, strerror(errno), fRet);

	bzero(buf, 4);
	buf[0] = C0H;
	fRet = write(i2c_fd, buf, 1);
	Debug(LOG_ERR,"I2C: %s: %s Write Len:%d",i2c_name, strerror(errno), fRet);

	bzero(buf, 4);
	buf[0] = 0xF0;
	buf[1] = 0;
	fRet = write(i2c_fd, buf, 1);
	Debug(LOG_ERR,"I2C: %s: %s Write Len:%d",i2c_name, strerror(errno), fRet);

	return 0;
}

int test_mmap()
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
       return 0;
   }

   p_mem = mmap(NULL, page_size * 2, PROT_READ | PROT_WRITE, MAP_SHARED, fd, BASE_ADDR);
   if(p_mem == NULL)
   {
       perror("mmap");
       close(fd);
       return 0;
   }

   close(fd);

   offset = GPIO_REG_OFFSET + 0x48;  /* Will aim at the first of the PC control registers, which controls PC7-PC0 */
                                       /* Page 377 in the manual */

   gpio = (volatile uint32_t *) ( (char *) (p_mem) + offset);
   printf("GPIOs at %p\n", gpio);

   *(gpio) &= ~(7 << 16);  /* Set SELECT to 000 for enable or input */
   *(gpio) |= (1 << 16);   /* Set SELECT to 001 for output */

   offset = GPIO_REG_OFFSET + 0x58;  /* Will aim at the the PC data register, which controls state of PC18-PC0 wires */
                                       /* Page 380 in the manual. */
   gpio = (volatile uint32_t *) ( (char *) (p_mem) + offset);
   printf("GPIOs at %p\n", gpio);

   /* flash on and off 20 times */
   //for(j = 0; j<200; j++)
   while(1){
       *(gpio) &= ~(0x10);  /* Set bit 4 for PC4 to 0 */
//       usleep(50000);
       sleep(2);
       *(gpio) |= (0x10);   /* Set bit 4 for PC4 to 1 */
       usleep(50000);
   }

   munmap(p_mem, page_size*2);

   return 0;


}
