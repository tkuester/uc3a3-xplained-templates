#include <board.h>
#include <delay.h>
#include <led.h>

int main(void)
{
    board_init();
    sysclk_init();

    while(1) {
        LED_Toggle(LED0);
        delay_ms(500);
    }
}
