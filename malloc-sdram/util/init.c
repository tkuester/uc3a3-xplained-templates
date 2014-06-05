#include <asf.h>
#include <gpio.h>
#include <usart.h>
#include <stdio_serial.h>

#include "util.h"
#include "conf_usart_serial.h"

void serial_init(void) {

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
