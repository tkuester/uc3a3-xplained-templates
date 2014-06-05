#include <asf.h>

#include "util.h"
#include "conf_usart_serial.h"

int _init_startup(void);
int _init_startup(void)
{
	// Import the Exception Vector Base Address.
	// Load the Exception Vector Base Address in the corresponding system register
	extern void _evba;
	Set_system_register(AVR32_EVBA, (int)&_evba);

    // As much as I'd like to printf in here, it doesn't seem to like this.
    // Ideally, stdio would be initilized, so main would LITERALLY be just
    // main, with no weird vendor code. If anyone can figure this out,
    // let me know.

    board_init();
    sysclk_init();
    //serial_init();
	sdramc_init(sysclk_get_hsb_hz());

	// Enable exceptions.
	// Initialize interrupt handling.
	Enable_global_exception();
	INTC_init_interrupts();

    /*
    if(memcheck() > 0) {
        hexdump("sdram", SDRAM, 256);
        while(1) {
            LED_Toggle(LED0);
            delay_ms(1500);
        }
    }
    */

	// GCC: Don't-care value.
	return 1;
}

void serial_init(void)
{
	// This is a fairly stereotypical "ASF pattern" for enabling a peripheral.

	// Setup the UART Options
	static const usart_serial_options_t UART_SERIAL_OPTS = {
		.baudrate = UART_BAUDRATE,
		.charlength = UART_CHAR_LENGTH,
		.paritytype = UART_PARITY,
		.stopbits = UART_STOP_BIT
	};

	// You could do this with one function call per pin, but this is "tidier"
	static const gpio_map_t UART_GPIO_MAP = {
		{UART_RX_PIN, UART_RX_FUNC},
		{UART_TX_PIN, UART_TX_FUNC}
	};

	// Enable the clock, module pins, and configure the module.
	// Note that the module config also sets up stdin/stdout for you.
	sysclk_enable_peripheral_clock(UART_PORT);
	gpio_enable_module(UART_GPIO_MAP,
			   sizeof(UART_GPIO_MAP) / sizeof(UART_GPIO_MAP[0]));
	stdio_serial_init(UART_PORT, &UART_SERIAL_OPTS);
}
