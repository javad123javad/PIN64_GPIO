/*
 * DbgLib.h
 *
 *  Created on: Feb 14, 2019
 *      Author: javad
 */

#ifndef DBGLIB_H_
#define DBGLIB_H_

typedef enum _LOG_LEVEL
{
	LOG_ERR = -1,
	LOG_WRN = -2,
	LOG_INF = -3
} LOG_LEVEL;

LOG_LEVEL Debug(LOG_LEVEL Severity, char * log_str, ...);

#endif /* DBGLIB_H_ */
