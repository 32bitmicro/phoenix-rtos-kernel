/*
 * Phoenix-RTOS
 *
 * Operating system kernel
 *
 * HAL console
 *
 * Copyright 2012, 2016 Phoenix Systems
 * Copyright 2001, 2005 Pawel Pisarczyk
 * Author: Pawel Pisarczyk
 *
 * This file is part of Phoenix-RTOS.
 *
 * %LICENSE%
 */

#ifndef _HAL_CONSOLE_H_
#define _HAL_CONSOLE_H_

/* Console attributes */
#define ATTR_NORMAL  0x03
#define ATTR_BOLD    0x0f
#define ATTR_USER    0x07


extern void hal_consolePrint(int attr, const char *s);


extern void _hal_consoleInit(void);

#endif
