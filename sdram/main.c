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

    // SDRAM comes from sdramc.h, and points to the start of the
    // external memory. You can make a uint32 pointer to it, and
    // access it like an array up to SDRAM_SIZE.
    //
    // You can still use malloc() in this example, but it gets
    // put inside the internal ram. See sdram-malloc if you want
    // to move the heap to SDRAM
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
