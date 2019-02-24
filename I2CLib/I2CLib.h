/*
 * I2CLib.h
 *
 *  Created on: Feb 15, 2019
 *      Author: javad
 */

#ifndef I2CLIB_H_
#define I2CLIB_H_

#define DISP_ON 	0x88
#define DISP_OFF	0x80
#define C0H 0xC0
int i2c_init();
int test_mmap();

#endif /* I2CLIB_H_ */
