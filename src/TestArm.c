/*
 ============================================================================
 Name        : TestArm.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ComLib.h"
#include "DbgLib.h"
#include "TestArm.h"

#define _DEBUG_EN_

int main_ComLib(void) {

	COM_PARA com_para;
	int comFd = 0, iLen = 0;
	char readBuff[BUFF_SIZE] = {0};
	strcpy(com_para.Port_name,"/dev/ttyS2");
	com_para.Baud_rate = B38400;
	com_para.CST = CS8;
	com_para.FLAGS |= BLOCKING;//WAIT_FOR_RN;
	//Fixme Remove the first parameter.

	comFd = com_init(&com_para);

	if(comFd < 0)
	{
		perror("com_init");
	}
	while(1)
	{
		bzero(readBuff, BUFF_SIZE);
		iLen = com_read(comFd, 32, readBuff);
		Debug(LOG_INF,"Read: %s\t size:%d",readBuff, iLen);
		com_write(comFd, iLen, readBuff);
		usleep((iLen+25)*100);
	}
	com_close(comFd);

	return EXIT_SUCCESS;
}
