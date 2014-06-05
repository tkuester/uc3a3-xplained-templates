#include <asf.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

// See this app note for putting the data and heap in external SDRAM
// http://www.atmel.com/Images/doc32121.pdf

/*
 * Malloc 1024 bytes... [ OK ]
 * Global var @ 0x654
 * Local var  @ 0xffe8
 * Heap var   @ 0xd0000188
 */

char external[100];

int main(void)
{
    serial_init();
    printf("Hello world!\n");
    
    printf("Malloc 1024 bytes... ");
    int i = 0;
    char *data = malloc(1024 * sizeof(char));

    printf("[%s]\n", (data == NULL ? "FAIL" : " OK "));
    printf("Global var @ %p\n", external);
    printf("Local var  @ %p\n", &i);
    printf("Heap var   @ %p\n", data);

    while(1) {
        printf("Toggle! %d\n", i++);
        LED_Toggle(LED0);
        delay_ms(500);
    }
}
