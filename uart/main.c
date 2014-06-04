#include <asf.h>
#include <stdio.h>

#include "util.h"

int main(void)
{
    board_init();
    sysclk_init();
    serial_init();

    printf("Hello world!\n");

    int i = 0;
    while(1) {
        printf("Toggle! %d\n", i++);
        LED_Toggle(LED0);
        delay_ms(500);
    }
}
