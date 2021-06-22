#include <platform.h>
#include <platform/iomap.h>
#include <platform/uart_dm.h>
#include <dev/uart.h>
#include <lk/debug.h>

void target_early_init(void) {
    uart_dm_init(2, 0, BLSP1_UART1_BASE);
}

void target_init(void) {
}
