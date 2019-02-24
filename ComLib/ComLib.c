/*
 * ComLib.c
 *
 *  Created on: Feb 14, 2019
 *      Author: javad
 */

#include "ComLib.h"
#include "DbgLib.h"
#include "Global.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
volatile int STOP=FALSE;


/* Function Section */
int com_init(const COM_PARA * com_para )
{

	int fd;
	struct termios tty;
	memset (&tty, 0, sizeof tty);
	fd = open (com_para->Port_name, O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0)
	{
		Debug(LOG_ERR,"error %d opening %s: %s", errno, com_para->Port_name, strerror (errno));
		return -1;
	}
	if (tcgetattr (fd, &tty) != 0)
	{
		Debug(LOG_ERR,"error %d from tcgetattr", errno);
		return -1;
	}

	cfsetospeed (&tty, com_para->Baud_rate);
	cfsetispeed (&tty, com_para->Baud_rate);

	tty.c_cflag = (tty.c_cflag & ~CSIZE) | com_para->CST;     // 8-bit chars
	// disable IGNBRK for mismatched speed tests; otherwise receive break
	// as \000 chars
	tty.c_iflag &= ~IGNBRK;         // disable break processing
	if(com_para->FLAGS & WAIT_FOR_RN)
		tty.c_lflag = ICANON;                // no signaling chars, no echo,// no canonical processing
	else
		tty.c_lflag = 0;//ICANON;                // no signaling chars, no echo,// no canonical processing

	tty.c_oflag = 0;                // no remapping, no delays

	if(com_para->FLAGS & BLOCKING)
	{
		tty.c_cc[VMIN]  = 1;            // read in blocking mode.
	}
	else
	{
		tty.c_cc[VMIN]  = 0;            // read doesn't block
	}
	tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

	tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
	// enable reading
	tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
	tty.c_cflag |= com_para->Parity;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CRTSCTS;

	if (tcsetattr (fd, TCSANOW, &tty) != 0)
	{
		Debug(LOG_ERR,"error %d from tcsetattr", errno);
		return -1;
	}
	return fd;
}

/************************************************************************
 * author: javad
 * date: Feb 14, 2019
 * brief:
 * Read blocks program execution until a line terminating character is
 * input, even if more than read_size chars are input. If the number
 * of characters read is smaller than the number of chars available,
 * subsequent reads will return the remaining chars. res will be set
 * to the actual number of characters actually read
 * parameters:
 * enclosing_method_arguments
 * return_type
 ************************************************************************/
int com_read(int fd, const ssize_t i_rd_len, char * o_buff)
{
	int res;
	//char buff[BUFF_SIZE] = {0};

	res = read(fd,o_buff,i_rd_len);
	o_buff[res]=0;             /* set end of string, so we can printf */

	return res;
}

/************************************************************************
 * author: javad
 * date: Feb 14, 2019
 * brief:
 * parameters:
 * enclosing_method_arguments
 * return_type
 ************************************************************************/
int com_write(int fd, const ssize_t i_wr_len, char * i_buff)
{
	int fRet = 0;

	fRet = write(fd, i_buff, i_wr_len);
	Debug(LOG_INF,"Bytes Written: %d", fRet);
	return fRet;
}

void
set_blocking (int fd, int should_block)
{
	struct termios tty;
	memset (&tty, 0, sizeof tty);
	if (tcgetattr (fd, &tty) != 0)
	{
		Debug(LOG_ERR,"error %d from tggetattr", errno);
		return;
	}

	tty.c_cc[VMIN]  = should_block ? 1 : 0;
	tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

	if (tcsetattr (fd, TCSANOW, &tty) != 0)
		Debug(LOG_ERR,"error %d setting term attributes", errno);
}

int com_close(int fd)
{
	return close(fd);
}
