#ifndef __UTIL_H
#define __UTIL_H

#include <stdint.h>

void serial_init(void);
uint32_t memcheck(void);
void hexdump(char *desc, void *addr, int len);

#endif
