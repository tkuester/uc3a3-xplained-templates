#include <asf.h>
#include <FreeRTOS.h>
#include <task.h>

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

uint8_t i;

static void blink_task(void *params __attribute__((unused)));
static void blink_task(void *params __attribute__((unused)))
{
    while(1) {
        LED_Toggle(LED0);
        vTaskDelay(500);
    }
}

static void malloc_task(void *params __attribute__((unused)));
static void malloc_task(void *params __attribute__((unused)))
{
    // Allocate 1 MB of data
    uint8_t *data = (uint8_t *)pvPortMalloc(1 << 20);
    printf("Global Variable: %p\n", &i);
    printf("Task Variable:   %p\n", &data);
    printf("Heap Data:       %p\n", data);

    vPortFree(data);
    vTaskDelete(NULL);
}

int main(void)
{
    serial_init();

    xTaskCreate(blink_task,
            (const signed char *)"Blink Task",
            configMINIMAL_STACK_SIZE,
            NULL,
            1,
            NULL);

    // This task needs quite a bit more stack to use printf
    xTaskCreate(malloc_task,
            (const signed char *)"Malloc Task",
            configMINIMAL_STACK_SIZE * 4,
            NULL,
            1,
            NULL);

    vTaskStartScheduler();

    while(1) {
        cpu_relax();
    }
}
