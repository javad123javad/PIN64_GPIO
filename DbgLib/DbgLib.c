/*
 * DbgLib.c
 *
 *  Created on: Feb 14, 2019
 *      Author: javad
 */

#include "DbgLib.h"
#include <stdio.h>
#include <stdarg.h>
LOG_LEVEL Debug(LOG_LEVEL Severity, char * log_str, ...)
{
	char buffer[4096];

	va_list args;
	va_start(args, log_str);
	vsnprintf(buffer, sizeof(buffer), log_str, args);
	va_end(args);

	switch (Severity) {
	case LOG_ERR:
		fprintf(stderr,"[LOG-ERROR]: %s\n", buffer);

		break;
	case LOG_WRN:
		fprintf(stderr,"[LOG-WARNNING]: %s\n", buffer);
		break;
	case LOG_INF:
		fprintf(stderr,"[LOG-INFO]: %s\n", buffer);
		break;
	default:
		fprintf(stderr,"[LOG-UNKOWN]: %s\n", buffer);
		break;
	}
	return Severity;
}
