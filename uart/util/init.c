#include <asf.h>
#include <gpio.h>
#include <usart.h>
#include <stdio_serial.h>

#include "util.h"
#include "conf_usart_serial.h"

void serial_init(void) {

    static const usart_serial_options_t UART_SERIAL_OPTS = {
        .baudrate = UART_BAUDRATE,
        .charlength = UART_CHAR_LENGTH,
        .paritytype = UART_PARITY,
        .stopbits = UART_STOP_BIT
    };

    static const gpio_map_t UART_GPIO_MAP = {
        {UART_RX_PIN, UART_RX_FUNC},
        {UART_TX_PIN, UART_TX_FUNC}
    };

    sysclk_enable_peripheral_clock(UART_PORT);
    gpio_enable_module(UART_GPIO_MAP,
            sizeof(UART_GPIO_MAP) / sizeof(UART_GPIO_MAP[0]));
    stdio_serial_init(UART_PORT, &UART_SERIAL_OPTS);
}
