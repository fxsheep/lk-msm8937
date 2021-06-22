#include <lk/reg.h>
#include <stdio.h>
#include <lk/trace.h>
#include <lib/cbuf.h>
#include <kernel/thread.h>
#include <platform/interrupts.h>
#include <dev/uart.h>

int uart_putc(int port, char c) {
    return 0;
}

int uart_getc(int port, bool wait) {
        return -1;
}

enum handler_return uart_irq_handler(void *arg) {

    return INT_RESCHEDULE;
}

void uart_init_early(void) {

}
void uart_init(void) {

}
