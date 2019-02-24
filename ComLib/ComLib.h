/*
 * ComLib.h
 *
 *  Created on: Feb 14, 2019
 *      Author: javad
 */

#ifndef COMLIB_H_
#define COMLIB_H_
#include <stdint.h>
#include <stdio.h>
#include <termios.h>
/**
 * Here we define macros, constants and global variables. Try avoid using
 * global variables.
 */


/* baudrate settings are defined in <asm/termbits.h>, which is
        included by <termios.h> */
#define BAUDRATE B38400
/* change this definition for the correct port */
#define MODEMDEVICE "/dev/ttyS1"
#define _POSIX_SOURCE 1 /* POSIX compliant source */

#define FALSE 0
#define TRUE 1
/* COM PARAMETERS */
#define WAIT_FOR_RN	ICANON	/* Wait until a terminating character received (\r, \n etc...) */
#define BLOCKING	0000004 /* Wait until receive a character */

typedef struct _COM_PARA
{
	char Port_name[64 + 1];
	unsigned short Baud_rate;
	unsigned short CST;
	unsigned short Parity;
	unsigned char FLAGS;
}COM_PARA;
#define BUFF_SIZE	1024
/* Function prototype */
int com_init(const COM_PARA * com_para );
int com_read(int fd, const ssize_t i_rd_len, char * o_buff);
int com_write(int fd, const ssize_t i_wr_len, char * i_buff);
int com_close(int fd);
#endif /* COMLIB_H_ */
