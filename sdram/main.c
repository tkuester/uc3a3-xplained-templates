#include <asf.h>
#include <stdio.h>

#include "util.h"

int main(void)
{
    board_init();
    sysclk_init();

    irq_initialize_vectors();
    cpu_irq_enable();

    sdramc_init(sysclk_get_hsb_hz());
    serial_init();

    printf("Sysclk: %lu Hz\n", sysclk_get_cpu_hz());
    printf("HSB: %lu Hz\n", sysclk_get_hsb_hz());
    printf("PBA: %lu Hz\n", sysclk_get_pba_hz());
    printf("PBB: %lu Hz\n", sysclk_get_pbb_hz());

    memcheck();
    hexdump("sdram", SDRAM, 256);

    printf("Hello world!\n");

    int i = 0;
    while(1) {
        printf("Toggle! %d\n", i++);
        LED_Toggle(LED0);
        delay_ms(500);
    }
}
