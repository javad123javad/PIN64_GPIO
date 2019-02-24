/*
 * main.c
 *
 *  Created on: Feb 14, 2019
 *      Author: javad
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ComLib.h"
#include "DbgLib.h"
#include "TestArm.h"

int
main(void)
{
//	i2c_init();
	test_mmap();

	return 0;
}
